#define STB_IMAGE_IMPLEMENTATION
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "move_sphere.h"
#include <float.h>
#include "camera.h"
#include "material.h"
#include <fstream>
#include "stb_image.h"
#include <string>
#include "rectangles.h"
#include "box.h"
#include "translate.h"
#include "rotate.h"
#include "fog.h"

const int width = 400;
const int height = 300;
const int sampleNum = 10;

vec3 paint(const ray& r, hitable* world, int depth);
hitable* scene();
hitable* twoperlin();
hitable* image_sphere();
hitable* light_sphere();
hitable* room();
hitable* fog_room();

int main()
{ 
	std::ofstream file;
	file.open("output.ppm");
	if (!file.is_open())
	{
		std::cout << "file open failed";
		return -1;
	}
	file << "P3\n" << width << " " << height << std::endl << "255" << std::endl;
	vec3 lookfrom(278.0f, 278.0f, -800.0f);
	vec3 lookat(278.0f, 278.0f, 0.0f);
	float distance_to_focus = 10.0f;
	float aperture = 0.0f;
	camera c(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), 40.0f, float(width) / float(height), aperture, distance_to_focus, 0.0f, 1.0f);
	hitable* world = image_sphere();
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			vec3 color(0.0f, 0.0f, 0.0f);
			for (int k = 0; k < sampleNum; k++)
			{
				float u = float(j + random_float()) / float(width);
				float v = float(i + random_float()) / float(height);
				ray r = c.get_ray(u, v);
				color += paint(r, world, 0);
			}
			color /= float(sampleNum);
			color = vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
			int ir = int(255.99f * color[0]);
			int ig = int(255.99f * color[1]);
			int ib = int(255.99f * color[2]);
			file << ir << " " << ig << " " << ib << " " << std::endl;
		}
	}
	return 0;
}

vec3 paint(const ray& r, hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) 
	{
		ray scattered;
		vec3 attenuation;
		vec3 emit = rec.material_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.material_ptr->scatter(r, rec, attenuation, scattered)) 
		{
			return emit + attenuation * paint(scattered, world, depth + 1);
		}
		else 
		{
			//return emit;
			return vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else 
	{
		vec3 unit_direction = normalized_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
		//return vec3(0.0f, 0.0f, 0.0f);
	}
}

hitable* twoperlin()
{
	hitable** list = new hitable*[2];
	texture* pertex = new noise_texture(4.0f);
	/*list[0] = new sphere(1000, vec3(0, -1000, 0), new lambertian(new checker_texture(new const_texture(vec3(0.1f, 0.1f, 0.1f)), new const_texture(vec3(0.6f, 0.0f, 0.0f)))));
	list[1] = new sphere(2, vec3(0, 2, 0), new lambertian(new checker_texture(new const_texture(vec3(0.2f, 0.3f, 0.1f)), new const_texture(vec3(0.9f, 0.9f, 0.9f)))));*/
	list[0] = new sphere(1000.0f, vec3(0.0f, -1000.0f, 0.0f), new lambertian(pertex));
	list[1] = new sphere(2.0f, vec3(0.0f, 2.0f, 0.0f), new lambertian(pertex));
	return new hitable_list(list, 2);
}

hitable* image_sphere()
{
	int nx, ny, nn;
	unsigned char* data = stbi_load("earthmap.png", &nx, &ny, &nn, 0);
	std::cout << nx << ' ' << ny << ' ' << nn << std::endl;
	if (data == NULL)
	{
		std::cout << "load image error";
		return NULL;
	}
	hitable* earth = new sphere(2.0f, vec3(0.0f, 0.0f, 0.0f), new lambertian(new image_texture(data, ny, nx, nn)));
	return earth;
}

hitable* light_sphere()
{
	texture* pertex = new noise_texture(4.0f);
	hitable** list = new hitable * [3];
	list[0] = new xy_rectangle(3.0f, 5.0f, 1.0f, 3.0f, -2.0f, new diffuse_light(new const_texture(vec3(1.0f, 1.0f, 1.0f))));
	list[1] = new sphere(1000, vec3(0, -1000, 0), new lambertian(pertex));
	list[2] = new sphere(2, vec3(0, 2, 0), new lambertian(pertex));
	return new hitable_list(list, 3);
}

hitable* room()
{
	material* red = new lambertian(new const_texture(vec3(0.65f, 0.05f, 0.05f)));
	material* white = new lambertian(new const_texture(vec3(1.0f, 1.0f, 1.0f)));
	material* green = new lambertian(new const_texture(vec3(0.12f, 0.45f, 0.15f)));
	material* light = new diffuse_light(new const_texture(vec3(1.0f, 1.0f, 1.0f)));
	hitable** list = new hitable*[8];
	int i = 0;
	list[i++] = new flip_normal(new yz_rectangle(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rectangle(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rectangle(213, 343, 227, 332, 554, light);
	list[i++] = new flip_normal(new xz_rectangle(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rectangle(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normal(new xy_rectangle(0, 555, 0, 555, 555, white));
	list[i++] = new box(vec3(130, 0, 65), vec3(295, 165, 230), white);
	list[i++] = new box(vec3(265, 0, 295), vec3(430, 330, 460), white);
	return new hitable_list(list, i);
}

hitable* fog_room()
{
	hitable** list = new hitable * [8];
	int i = 0;
	material* red = new lambertian(new const_texture(vec3(0.65, 0.05, 0.05)));
	material* white = new lambertian(new const_texture(vec3(0.73, 0.73, 0.73)));
	material* green = new lambertian(new const_texture(vec3(0.12, 0.45, 0.15)));
	material* light = new diffuse_light(new const_texture(vec3(7, 7, 7)));
	list[i++] = new flip_normal(new yz_rectangle(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rectangle(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rectangle(113, 443, 127, 432, 554, light);
	list[i++] = new flip_normal(new xz_rectangle(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rectangle(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normal(new xy_rectangle(0, 555, 0, 555, 555, white));

	hitable* b1 = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), white), -18), vec3(130, 0, 65));
	hitable* b2 = new translate(new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white), 15), vec3(265, 0, 295));

	list[i++] = new constant_medium(b1, 0.01, new const_texture(vec3(1.0, 1.0, 1.0)));
	list[i++] = new constant_medium(b2, 0.01, new const_texture(vec3(0.0, 0.0, 0.0)));

	return new hitable_list(list, i);
}

hitable* scene()
{
	int n = 500;
	hitable** list = new hitable * [n + 1];
	list[0] = new sphere(1000, vec3(0.0f, -1000.0f, 0.0f), new lambertian(new checker_texture(new const_texture(vec3(0.2, 0.3, 0.1)),new const_texture(vec3(0.9, 0.9, 0.9)))));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = random_float();
			vec3 center(a + 0.9 * random_float(), 0.2f, b + 0.9 * random_float());
			if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f)
			{
				if (choose_mat < 0.8f) //diffuse
				{
					//list[i++] = new sphere(0.2f, center, new lambertian(new const_texture(vec3(random_float() * random_float(), random_float() * random_float(), random_float() * random_float()))));
					list[i++] = new move_sphere(0.2f, center, center + vec3(0.0f, 0.5f * random_float(), 0.0f), new lambertian(new const_texture(vec3(random_float() * random_float(), random_float() * random_float(), random_float() * random_float()))), 0.0f, 1.0f);
				}
				else if (choose_mat < 0.95f) //metal
				{
					list[i++] = new sphere(0.2f, center, new metal(vec3(0.5f * (1 + random_float()), 0.5f * (1 + random_float()), 0.5f * (1 + random_float())), 0.5f * random_float()));
				}
				else //glass
				{
					list[i++] = new sphere(0.2f, center, new dielectric(1.5f));
				}
			}
		}
	}
	list[i++] = new sphere(1.0f, vec3(0.0f, 1.0f, 0.0f), new dielectric(1.5f));
	list[i++] = new sphere(1.0f, vec3(-4.0f, 1.0f, 0.0f), new lambertian(new const_texture(vec3(0.4f, 0.2f, 0.1f))));
	list[i++] = new sphere(1.0f, vec3(4.0f, 1.0f, 0.0f), new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f));
	return new hitable_list(list, i);
}