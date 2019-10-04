#ifndef SPHERE
#define SPHERE
#include "hitable.h"
#include "material.h"

class sphere : public hitable
{
private :
	float radius;
	vec3 center;
	material* m;
public :
	sphere() { radius = 0; }
	sphere(float radius, vec3 center, material* material) : radius(radius), center(center), m(material)
	{

	}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		vec3 oc = r.origin() - center;
		float a = dot(r.direction(), r.direction());
		float b = 2.0f * dot(r.direction(), oc);
		float c = dot(oc, oc) - radius * radius;
		float delta = b * b - 4 * a * c;
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
				return true;
			}
			x = (-b + sqrt(delta)) / (2 * a);
			if (x < t_max && x > t_min)
			{
				rec.t = x;
				rec.p = r.point_at_parameter(x);
				rec.normal = (rec.p - center) / radius;
				rec.material_ptr = m;
				return true;
			}
			return false;
		}
	}
};

#endif // !SPHERE