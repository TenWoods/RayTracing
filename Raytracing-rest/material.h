#ifndef MATERIAL
#define MATERIAL
#include "ray.h"
#include "hitable.h"
#include "random.h"
#include "texture.h"

class material
{
public :
	virtual bool scatter(const ray& ray_in, hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
	//自发光(默认为黑色)
	virtual vec3 emitted(float u, float v, const vec3& point) const
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}
	//计算反射方向
	vec3 reflect(vec3 in, vec3 normal) const
	{
		vec3 result = in + 2 * dot(-in, normal) * normal;
		return result;
	}
	//获取单位球中随机一点(diffuse用)
	vec3 random_sphere_point() const
	{
		vec3 p;
		do
		{
			p = 2.0f * vec3(random_float(), random_float(), random_float()) - vec3(1.0f, 1.0f, 1.0f);
		} while (p.squared_length() >= 1.0f);
		return p;
	}
	//折射方向
	bool refract(const vec3& in, const vec3& normal, float ni_over_no, vec3& refracted) const
	{
		vec3 nin = normalized_vector(in);
		float cosi = dot(nin, normal);
		float cost = 1.0f - ni_over_no * ni_over_no * (1.0f - cosi * cosi);
		if (cost > 0)
		{
			refracted = ni_over_no * (nin - normal * cosi) - normal * sqrt(cost);
			return true;
		}
		return false;
	}
};

//diffuse
class lambertian : public material
{
private:
	texture* albedo;
public:
	lambertian(texture* a) : albedo(a) {}
	virtual bool scatter(const ray& ray_in, hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 next_direction = rec.p + rec.normal + random_sphere_point();
		scattered = ray(rec.p, next_direction - rec.p, ray_in.time());
		attenuation = albedo->value(0.0f, 0.0f, rec.p);
		return true;
	}
};

//metal
class metal : public material
{
private:
	vec3 albedo;
	float fuzz;
public:
	metal(vec3 a, float f) : albedo(a)
	{
		if (f < 1)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1.0f;
		}
	}
	virtual bool scatter(const ray& ray_in, hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 next_direction = reflect(normalized_vector(ray_in.direction()), rec.normal);
		scattered = ray(rec.p, next_direction + fuzz * random_sphere_point(), ray_in.time());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

//glass
class dielectric : public material
{
private:
	float ref_idx;
public:
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const ray& ray_in, hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 outward_normal;
		float ni_over_no;
		float cosine;
		float reflect_prob;
		vec3 reflected = reflect(ray_in.direction(), rec.normal);
		attenuation = vec3(1.0f, 1.0f, 1.0f);
		vec3 refracted;
		if (dot(ray_in.direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_no = ref_idx;
			cosine = dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
			//cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_no = 1.0f / ref_idx;
			cosine = -dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
		}
		if (refract(ray_in.direction(), outward_normal, ni_over_no, refracted))
		{
			reflect_prob = schlick(cosine, ref_idx);
		}
		else
		{
			reflect_prob = 1.0f;
		}
		if (random_float() < reflect_prob)
		{
			scattered = ray(rec.p, reflected, ray_in.time());
		}
		else
		{
			scattered = ray(rec.p, refracted, ray_in.time());
		}
		return true;
	}
	float schlick(float cosine, float ref_idx) const
	{
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

};

//光源
class diffuse_light : public material
{
private :
	texture* tex;
public :
	diffuse_light() {}
	diffuse_light(texture* t) : tex(t) {}
	virtual bool scatter(const ray& ray_in, hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		return false;
	}
	virtual vec3 emitted(float u, float v, const vec3& point) const
	{
		return tex->value(u, v, point);
	}
};

#endif