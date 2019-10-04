#include "vec3.h"

vec3::vec3(float x, float y, float z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

vec3& vec3::operator+=(const vec3& vec_2)
{
	vec[0] += vec_2.vec[0];
	vec[1] += vec_2.vec[1];
	vec[2] += vec_2.vec[2];
	return *this;
}
vec3& vec3::operator-=(const vec3& vec_2)
{
	vec[0] -= vec_2.vec[0];
	vec[1] -= vec_2.vec[1];
	vec[2] -= vec_2.vec[2];
	return *this;
}
vec3& vec3::operator*=(const vec3& vec_2)
{
	vec[0] *= vec_2.vec[0];
	vec[1] *= vec_2.vec[1];
	vec[2] *= vec_2.vec[2];
	return *this;
}
vec3& vec3::operator/=(const vec3& vec_2)
{
	vec[0] /= vec_2.vec[0];
	vec[1] /= vec_2.vec[1];
	vec[2] /= vec_2.vec[2];
	return *this;
}
vec3& vec3::operator*=(const float f)
{
	vec[0] *= f;
	vec[1] *= f;
	vec[2] *= f;
	return *this;
}
vec3& vec3::operator/=(const float f)
{
	vec[0] /= f;
	vec[1] /= f;
	vec[2] /= f;
	return *this;
}

void vec3::normalize()
{
	float k = 1 / length();
	vec[0] *= k;
	vec[1] *= k;
	vec[2] *= k;
}

vec3 operator+(const vec3& v1, const vec3& v2)
{
	return vec3(v1.vec[0] + v2.vec[0], v1.vec[1] + v2.vec[1], v1.vec[2] + v2.vec[2]);
}
vec3 operator-(const vec3& v1, const vec3& v2)
{
	return vec3(v1.vec[0] - v2.vec[0], v1.vec[1] - v2.vec[1], v1.vec[2] - v2.vec[2]);
}
//颜色向量的乘除
vec3 operator*(const vec3& v1, const vec3& v2)
{
	return vec3(v1.vec[0] * v2.vec[0], v1.vec[1] * v2.vec[1], v1.vec[2] * v2.vec[2]);
}
vec3 operator/(const vec3& v1, const vec3& v2)
{
	return vec3(v1.vec[0] / v2.vec[0], v1.vec[1] / v2.vec[1], v1.vec[2] / v2.vec[2]);
}
//普通向量的点乘
float dot(const vec3& v1, const vec3& v2)
{
	return (v1.vec[0] * v2.vec[0] + v1.vec[1] * v2.vec[1] + v1.vec[2] * v2.vec[2]);
}
//叉乘
vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3(v1.vec[1] * v2.vec[2] - v1.vec[2] * v2.vec[1],
		-(v1.vec[0] * v2.vec[2] - v1.vec[2] * v2.vec[0]),
		v1.vec[0] * v2.vec[1] - v1.vec[1] * v2.vec[0]);
}
//普通向量的乘除
vec3 operator*(const vec3& v, float f)
{
	return vec3(v.vec[0] * f, v.vec[1] * f, v.vec[2] * f);
}
vec3 operator/(const vec3& v, float f)
{
	return vec3(v.vec[0] / f, v.vec[1] / f, v.vec[2] / f);
}
vec3 operator*(float f, const vec3& v)
{
	return vec3(v.vec[0] * f, v.vec[1] * f, v.vec[2] * f);
}

vec3 normalized_vector(vec3 v)
{
	return v / v.length();
}

std::istream& operator>>(std::istream& is, vec3& v)
{
	is >> v.vec[0] >> v.vec[1] >> v.vec[2];
	return is;
}
std::ostream& operator<<(std::ostream& os, vec3& v)
{
	os << v.vec[0] << " " << v.vec[1] << " " << v.vec[2];
	return os;
}