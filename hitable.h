#ifndef HITABLE
#define HITABLE
#include "ray.h"

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
};

#endif // !HITABLE
