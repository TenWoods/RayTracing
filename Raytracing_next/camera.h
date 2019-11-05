#ifndef CAMERA
#define CAMERA
#include "vec3.h"
#include "ray.h"
#include "random.h"

class camera
{
private :
	vec3 origin;
	vec3 lower_left;
	vec3 horizontal;
	vec3 vertical;
	float lens_radius;
	vec3 u, w, v;
	float time_0, time_1;
	const float PI = 3.1415926f;
public : 
	camera(vec3 lookfrom, vec3 lookat, vec3 vUp, float fov, float aspect, float aperture, float focus_distance, float time0, float time1)
	{
		lens_radius = aperture / 2.0f;
		float theta = fov * PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		w = normalized_vector(lookfrom - lookat);
		u = normalized_vector(cross(vUp, w));
		v = cross(w, u);
		origin = lookfrom;
		lower_left = origin - focus_distance * half_width * u - focus_distance * half_height * v - focus_distance * w;
		horizontal = 2 * focus_distance * half_width * u;
		vertical = 2 * focus_distance * half_height * v;
		time_0 = time0;
		time_1 = time1;
	}
	
	ray get_ray(float s, float t)
	{
		vec3 rd = lens_radius * random_disk_point();
		vec3 offset = u * rd.x() + v * rd.y();
		float time = time_0 + random_float() * (time_1 - time_0);
		return ray(origin + offset, lower_left + s * horizontal + t * vertical - origin - offset, time);
	}

	vec3 random_disk_point() const
	{
		vec3 p;
		do 
		{
			p = 2.0f * vec3(random_float(), random_float(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
		} while (dot(p, p) >= 1.0);
		return p;
	}
};

#endif // !CAMERA
