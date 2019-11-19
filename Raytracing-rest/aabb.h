#pragma once
#include "vec3.h"
#include "ray.h"
inline float ffmax(float f1, float f2)
{
	return f1 < f2 ? f2 : f1;
}

inline float ffmin(float f1, float f2)
{
	return f1 < f2 ? f1 : f2;
}

//AABBÅö×²ºÐ
class aabb
{
private :
	vec3 _min;
	vec3 _max;
public :
	aabb() {}
	aabb(const vec3& a, const vec3& b) : _min(a), _max(b) {}
	vec3 min() const
	{
		return _min;
	}
	vec3 max() const
	{
		return _max;
	}
	bool hit(const ray& r, float tmin, float tmax) const
	{
		for (int i = 0; i < 3; i++)
		{
			float t0 = (_min[i] - r.origin()[i]) / r.direction()[i];
			float t1 = (_max[i] - r.origin()[i]) / r.direction()[i];
			if (r.direction()[i] < 0)
			{
				float temp = t0;
				t0 = t1;
				t1 = temp;
			}
			tmin = ffmax(t0, tmin);
			tmax = ffmin(t1, tmax);
			if (tmax <= tmin)
				return false;
		}
		return true;
	}
};

static aabb surrounding_box(aabb box0, aabb box1)
{
	vec3 min = vec3(fmin(box0.min()[0], box1.min()[0]),
		fmin(box0.min()[1], box1.min()[1]),
		fmin(box0.min()[2], box1.min()[2]));
	vec3 max = vec3(fmax(box0.max()[0], box1.max()[0]),
		fmax(box0.max()[1], box1.max()[1]),
		fmax(box0.max()[2], box1.max()[2]));
	return aabb(min, max);
}