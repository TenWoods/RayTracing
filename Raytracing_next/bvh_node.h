#pragma once
#include "hitable.h"
#include "random.h"


int compare_x(const void* a, const void* b)
{
	aabb box_a, box_b;
	hitable* ah = *(hitable**)a;
	hitable* bh = *(hitable**)b;
	if (!ah->bounding_box(0.0f, 0.0f, box_a) || !bh->bounding_box(0.0f, 0.0f, box_b))
	{
		std::cerr << "no bounding box!";
	}
	if (box_a.min().x() < box_b.min().x())
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int compare_y(const void* a, const void* b)
{
	aabb box_a, box_b;
	hitable* ah = *(hitable * *)a;
	hitable* bh = *(hitable * *)b;
	if (!ah->bounding_box(0.0f, 0.0f, box_a) || !bh->bounding_box(0.0f, 0.0f, box_b))
	{
		std::cerr << "no bounding box!";
	}
	if (box_a.min().y() < box_b.min().y())
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int compare_z(const void* a, const void* b)
{
	aabb box_a, box_b;
	hitable* ah = *(hitable * *)a;
	hitable* bh = *(hitable * *)b;
	if (!ah->bounding_box(0.0f, 0.0f, box_a) || !bh->bounding_box(0.0f, 0.0f, box_b))
	{
		std::cerr << "no bounding box!";
	}
	if (box_a.min().z() < box_b.min().z())
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
class bvh_node : public hitable
{
private :
	hitable* right;
	hitable* left;
	aabb _box;
public :
	bvh_node() {}
	bvh_node(hitable** list, int n, float time0, float time1);

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		if (!_box.hit(r, t_min, t_max))
			return false;
		hit_record right_rec, left_rec;
		bool right_hit = right->hit(r, t_min, t_max, right_rec);
		bool left_hit = left->hit(r, t_min, t_max, left_rec);
		if (right_hit && left_hit)
		{
			if (right_rec.t < left_rec.t)
			{
				rec = right_rec;
			}
			else
			{
				rec = left_rec;
			}
			return true;
		}
		else if (right_hit)
		{
			rec = right_rec;
			return true;
		}
		else if (left_hit)
		{
			rec = left_rec;
			return true;
		}
		else
		{
			return false;
		}
	}
	virtual bool bounding_box(float time0, float time1, aabb& box) const
	{
		box = _box;
		return true;
	}
};

bvh_node::bvh_node(hitable** list, int n, float time0, float time1)
{
	int axis = int(3 * random_float());
	if (axis == 0)
	{
		qsort(list, n, sizeof(hitable*), compare_x);
	}
	else if (axis == 1)
	{
		qsort(list, n, sizeof(hitable*), compare_y);
	}
	else
	{
		qsort(list, n, sizeof(hitable*), compare_z);
	}
	if (n == 1)
	{
		left = right = list[0];
	}
	else if (n == 2)
	{
		left = list[0];
		right = list[1];
	}
	else
	{
		left = new bvh_node(list, (n / 2), time0, time1);
		right = new bvh_node(list + (n / 2), n - n / 2, time0, time1);
	}
	aabb box_left, box_right;
	if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
	{
		std::cerr << "no bounding box";
	}
	_box = surrounding_box(box_left, box_right);
}