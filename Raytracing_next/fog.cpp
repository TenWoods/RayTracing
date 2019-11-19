#pragma once
#include "hitable.h"
class constant_medium : public hitable {
public:
	constant_medium(hittable* b, float d, texture* a) : boundary(b), density(d) {
		phase_function = new isotropic(a);
	}
	virtual bool hit(
		const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		return boundary->bounding_box(t0, t1, box);
	}
	hittable* boundary;
	float density;
	material* phase_function;
};