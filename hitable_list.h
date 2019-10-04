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
		double closest_so_far = t_max;
		for (int i = 0; i < list_size; i++)
		{
			if (list[i]->hit(r, t_min, closest_so_far, temp))
			{
				hit_result = true;
				closest_so_far = temp.t;
				rec = temp;
			}
		}
		return hit_result;
	}
};

#endif // !HITABLELIST