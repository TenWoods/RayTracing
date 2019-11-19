#ifndef SPHERE
#define SPHERE
#include "hitable.h"
#include "material.h"
#include <math.h>

const float PI = 3.1415926f;

void get_sphere_uv(const vec3& point, float* u, float* v)
{
	float phi = atan2(point.z(), point.x());
	float theta = asin(point.y());
	*u = 1 - (phi + PI) / (2 * PI);
	*v = (theta + PI / 2) / PI;
}

class sphere : public hitable
{
private :
	float radius;
	vec3 center;
	material* m;
public :
	sphere() { }
	sphere(float radius, vec3 center, material* material) : radius(radius), center(center), m(material)
	{

	}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		vec3 oc = r.origin() - center;
		float a = dot(r.direction(), r.direction());
		float b = 2.0f * dot(r.direction(), oc);
		float c = dot(oc, oc) - radius * radius;
		float delta = b * b - 4.0f * a * c;
		if (delta < 0)
		{
			return false;
		}
		else
		{
			float x = (-b - sqrt(delta)) / (2 * a);
			if (x < t_max && x > t_min)
			{
				rec.t = x;
				rec.p = r.point_at_parameter(x);
				rec.normal = (rec.p - center) / radius;
				rec.material_ptr = m;
				get_sphere_uv(rec.normal, &rec.u, &rec.v);
				return true;
			}
			x = (-b + sqrt(delta)) / (2 * a);
			if (x < t_max && x > t_min)
			{
				rec.t = x;
				rec.p = r.point_at_parameter(x);
				rec.normal = (rec.p - center) / radius;
				rec.material_ptr = m;
				get_sphere_uv(rec.normal, &rec.u, &rec.v);
				return true;
			}
			return false;
		}
	}
	virtual bool bounding_box(float time0, float time1, aabb& box) const
	{
		vec3 min = center - vec3(radius, radius, radius);
		vec3 max = center + vec3(radius, radius, radius);
		box = aabb(min, max);
		return true;
	}
};

#endif // !SPHERE