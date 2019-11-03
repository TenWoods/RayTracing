#ifndef HITABLE
#define HITABLE
#include "ray.h"
#include "aabb.h"

class material;

struct hit_record
{
	float t;					//���ߵ�ǰ�����
	vec3 p;						//hit��
	vec3 normal;				//hit�㷨��
	material* material_ptr;		//������Ϣ
};

class hitable
{
public :
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(float time0, float time1, aabb& box) const = 0;
};

aabb surrounding_box(aabb box0, aabb box1)
{
	vec3 min = vec3(fmin(box0.min()[0], box1.min()[0]),
		fmin(box0.min()[1], box1.min()[1]),
		fmin(box0.min()[2], box1.min()[2]));
	vec3 max = vec3(fmax(box0.max()[0], box1.max()[0]),
		fmax(box0.max()[1], box1.max()[1]),
		fmax(box0.max()[2], box1.max()[2]));
	return aabb(min, max);
}

#endif // !HITABLE
