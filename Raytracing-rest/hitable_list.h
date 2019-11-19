#ifndef HITABLELIST
#define HITABLELIST
#include "hitable.h"

class hitable_list : public hitable
{
private :
	hitable** list;
	int list_size;
public :
	hitable_list() {}
	hitable_list(hitable** l, int size)
	{
		list = l;
		list_size = size;
	}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		hit_record temp;
		bool hit_result = false;
		double closest = t_max;
		for (int i = 0; i < list_size; i++)
		{
			//这里相当于深度测试
			if (list[i]->hit(r, t_min, closest, temp))
			{
				hit_result = true;
				closest = temp.t;
				rec = temp;
			}
		}
		return hit_result;
	}
	virtual bool bounding_box(float time0, float time1, aabb& box) const
	{
		if (list_size < 1)
			return false;
		aabb temp;
		bool first_test = list[0]->bounding_box(time0, time1, temp);
		if (!first_test)
			return false;
		else
			box = temp;
		for (int i = 1; i < list_size; i++)
		{
			if (list[i]->bounding_box(time0, time1, temp))
			{
				box = surrounding_box(box, temp);
			}
			else
				return false;
		}
		return true;
	}
};

#endif // !HITABLELIST