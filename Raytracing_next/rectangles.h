#pragma once
#include "aabb.h"
#include "hitable.h"

class xy_rectangle : public hitable
{
private :
	float x0, x1;
	float y0, y1;
	float z;
	material* m;
public :
	xy_rectangle() {}
	xy_rectangle(float x_0, float x_1, float y_0, float y_1, float _z, material* _m) : x0(x_0), x1(x_1), y0(y_0), y1(y_1), z(_z), m(_m) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		float t = (z - r.origin().z()) / r.direction().z();
		if (t < t_min || t > t_max)
		{
			return false;
		}
		float x = r.origin().x() + t * r.direction().x();
		float y = r.origin().y() + t * r.direction().y();
		if (x < x0 || x > x1 || y < y0 || y > y1)
		{
			return false;
		}
		rec.p = r.point_at_parameter(t);
		rec.t = t;
		rec.normal = normalized_vector(vec3(0.0f, 0.0f, 1.0f));
		rec.material_ptr = m;
		rec.u = (x - x0) / (x1 - x0);
		rec.v = (y - y0) / (y1 - y0);
		return true;
	}
	virtual bool bounding_box(float time0, float time1, aabb& box) const
	{
		box = aabb(vec3(x0, y0, z - 0.0001f), vec3(x1, y1, z + 0.0001f));
		return true;
	}
};

class xz_rectangle : public hitable
{
private:
	float x0, x1;
	float z0, z1;
	float y;
	material* m;
public:
	xz_rectangle() {}
	xz_rectangle(float x_0, float x_1, float z_0, float z_1, float _y, material* _m) : x0(x_0), x1(x_1), z0(z_0), z1(z_1), y(_y), m(_m) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		float t = (y - r.origin().y()) / r.direction().y();
		if (t < t_min || t > t_max)
		{
			return false;
		}
		float x = r.origin().x() + t * r.direction().x();
		float z = r.origin().z() + t * r.direction().z();
		if (x < x0 || x > x1 || z < z0 || z > z1)
		{
			return false;
		}
		rec.p = r.point_at_parameter(t);
		rec.t = t;
		rec.normal = normalized_vector(vec3(0.0f, 1.0f, 0.0f));
		rec.material_ptr = m;
		rec.u = (x - x0) / (x1 - x0);
		rec.v = (z - z0) / (z1 - z0);
		return true;
	}
	virtual bool bounding_box(float time0, float time1, aabb& box) const
	{
		box = aabb(vec3(x0, z0, y - 0.0001f), vec3(x1, z1, y + 0.0001f));
		return true;
	}
};

class yz_rectangle : public hitable
{
private:
	float y0, y1;
	float z0, z1;
	float x;
	material* m;
public:
	yz_rectangle() {}
	yz_rectangle(float x_0, float x_1, float z_0, float z_1, float _y, material* _m) : y0(x_0), y1(x_1), z0(z_0), z1(z_1), x(_y), m(_m) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		float t = (x - r.origin().x()) / r.direction().x();
		if (t < t_min || t > t_max)
		{
			return false;
		}
		float y = r.origin().y() + t * r.direction().y();
		float z = r.origin().z() + t * r.direction().z();
		if (y < y0 || y > y1 || z < z0 || z > z1)
		{
			return false;
		}
		rec.p = r.point_at_parameter(t);
		rec.t = t;
		rec.normal = normalized_vector(vec3(1.0f, 0.0f, 0.0f));
		rec.material_ptr = m;
		rec.u = (y - y0) / (y1 - y0);
		rec.v = (z - z0) / (z1 - z0);
		return true;
	}
	virtual bool bounding_box(float time0, float time1, aabb& box) const
	{
		box = aabb(vec3(y0, z0, x - 0.0001f), vec3(y1, z1, x + 0.0001f));
		return true;
	}
};