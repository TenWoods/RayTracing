#ifndef VEC
#define VEC

#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3
{
private : 
	float vec[3];
public : 
	vec3() { vec[0] = 0; vec[1] = 0; vec[2] = 0; }
	vec3(float x, float y, float z);

	float x() const { return vec[0]; }
	float y() const { return vec[1]; }
	float z() const { return vec[2]; }
	float r() const { return vec[0]; }
	float g() const { return vec[1]; }
	float b() const { return vec[2]; }

	inline const vec3& operator+() const 
	{ 
		return *this; 
	}
	inline vec3 operator-() const 
	{ 
		return vec3(-vec[0], -vec[1], -vec[2]); 
	}
	inline float operator[] (int i) const 
	{ 
		return vec[i]; 
	}
	inline float& operator[] (int i) 
	{
		return vec[i]; 
	}

	vec3& operator+=(const vec3& vec_2);
	vec3& operator-=(const vec3& vec_2);
	//颜色
	vec3& operator*=(const vec3& vec_2);
	vec3& operator/=(const vec3& vec_2);
	//普通向量
	vec3& operator*=(const float f);
	vec3& operator/=(const float f);

	inline float length() 
	{ 
		return sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]); 
	}
	inline float squared_length()
	{
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	}
	void normalize();

	friend vec3 operator+(const vec3& v1, const vec3& v2);
	friend vec3 operator-(const vec3& v1, const vec3& v2);
	//颜色向量的乘除
	friend vec3 operator*(const vec3& v1, const vec3& v2);
	friend vec3 operator/(const vec3& v1, const vec3& v2);
	//普通向量的点乘
	friend float dot(const vec3& v1, const vec3& v2);
	//叉乘
	friend vec3 cross(const vec3& v1, const vec3& v2);
	//普通向量的乘除
	friend vec3 operator*(const vec3& v, float f);
	friend vec3 operator/(const vec3& v, float f);
	friend vec3 operator*(float f, const vec3& v);

	friend vec3 normalized_vector(vec3 v);
	friend std::istream& operator>>(std::istream& is, vec3& v);
	friend std::ostream& operator<<(std::ostream& os, vec3& v);
};

vec3 operator+(const vec3& v1, const vec3& v2);
vec3 operator-(const vec3& v1, const vec3& v2);
//颜色向量的乘除
vec3 operator*(const vec3& v1, const vec3& v2);
vec3 operator/(const vec3& v1, const vec3& v2);
//普通向量的乘除
vec3 operator*(const vec3& v, float f);
vec3 operator/(const vec3& v, float f);
vec3 operator*(float f, const vec3& v);
//普通向量的点乘
float dot(const vec3& v1, const vec3& v2);
//叉乘
vec3 cross(const vec3& v1, const vec3& v2);

vec3 normalized_vector(vec3 v);
std::istream& operator>>(std::istream& is, vec3& v);
std::ostream& operator<<(std::ostream& os, vec3& v);

#endif // !VEC