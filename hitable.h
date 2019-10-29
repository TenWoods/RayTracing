#ifndef HITABLE
#define HITABLE
#include "ray.h"

class material;

struct hit_record
{
	float t;					//射线当前点参数
	vec3 p;						//hit点
	vec3 normal;				//hit点法线
	material* material_ptr;		//材质信息
};

class hitable
{
public :
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif // !HITABLE
