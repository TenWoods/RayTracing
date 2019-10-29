#ifndef RAY
#define RAY

#include "vec3.h"

class ray
{
private:
	vec3 A;
	vec3 B;
	float _time;
public :
	ray() {}
	ray(vec3 origin, vec3 direction, float time = 0.0f) : A(origin), B(direction), _time(time)
	{

	}
	vec3 origin() const
	{
		return A;
	}
	vec3 direction() const
	{
		return B;
	}
	vec3 point_at_parameter(float t) const
	{
		return A + t * B;
	}
	float time() const
	{
		return _time;
	}
};

#endif // !RAY