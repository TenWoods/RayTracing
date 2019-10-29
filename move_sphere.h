#pragma once
#ifndef MOVE_SPHERE
#define MOVE_SPHERE
#include "hitable.h"
#include "material.h"

class move_sphere : public hitable
{
private :
	float radius;
	vec3 center_0,center_1;
	material* m;
	float time_0, time_1;
public :
	move_sphere(float radius, vec3 center0, vec3 center1, material* material, float time0, float time1) : radius(radius), center_0(center0), center_1(center1), m(material), time_0(time0), time_1(time1)
	{

	}
	vec3 center(float time) const
	{
		return center_0 + ((time - time_0) / (time_1 - time_0)) * (center_1 - center_0);
	}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		vec3 oc = r.origin() - center(r.time());
		float a = dot(r.direction(), r.direction());
		float b = 2.0f * dot(r.direction(), oc);
		float c = dot(oc, oc) - radius * radius;
		float delta = b * b - 4.0f * a * c;
		if (delta < 0)
		{
			return false;
		}
		float x = (-b - sqrt(delta)) / (2 * a);
		if (x <= t_max && x >= t_min)
		{
			rec.t = x;
			rec.p = r.point_at_parameter(x);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.material_ptr = m;
			return true;
		}
		x = (-b + sqrt(delta)) / (2 * a);
		if (x <= t_max && x >= t_min)
		{
			rec.t = x;
			rec.p = r.point_at_parameter(x);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.material_ptr = m;
			return true;
		}
		return false;
	}

};
#endif // !MOVE_SPHERE
