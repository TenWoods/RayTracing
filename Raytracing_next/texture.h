#pragma once

#include "vec3.h"
#include "perlin.h"


class texture
{
public :
	virtual vec3 value(float u, float v, const vec3& point) const = 0;
};

//´¿ÑÕÉ«²ÄÖÊ
class const_texture : public texture
{
private : 
	vec3 color;
public :
	const_texture(vec3 c) : color(c)
	{

	}
	virtual vec3 value(float u, float v, const vec3& point) const
	{
		return color;
	}
};

class checker_texture : public texture
{
private :
	texture* odd;
	texture* even;
public :
	checker_texture() {}
	checker_texture(texture* tex0, texture* tex1) : odd(tex0), even(tex1) {}
	virtual vec3 value(float u, float v, const vec3& point) const
	{
		float sines = sin(10.0f * point.x()) * sin(10.0f * point.y()) * sin(10.0f * point.z());
		if (sines < 0.0f)
		{
			return odd->value(u, v, point);
		}
		else
		{
			return even->value(u, v, point);
		}
	}
};

class noise_texture : public texture
{
private :
	perlin noise;
	float _scale;
public:
	noise_texture() {}
	noise_texture(float scale) : _scale(scale) {}
	virtual vec3 value(float u, float v, const vec3& point) const
	{
		return vec3(1.0f, 1.0f, 1.0f) * 0.5f * (1.0f + sin(_scale * point.z() + 10.0f * noise.turbulence(point)));
	}
};

class image_texture : public texture
{
private :
	unsigned char* _data;
	int nx;
	int ny;
	int nn;
public :
	image_texture() {}
	image_texture(const char* dataPath);
	virtual vec3 value(float u, float v, const vec3& point) const
	{
		int i = (1 - u) * nx;
		int j = (1 - v) * ny - 0.001f;
		if (i < 0)
			i = 0;
		if (j < 0)
			j = 0;
		if (i > nx - 1)
			i = nx - 1;
		if (j > ny - 1)
			j = ny - 1;
		float r = _data[i * nn + j * nn * nx] / 255.0f;
		float g = _data[i * nn + j * nn * nx + 1] / 255.0f;
		float b = _data[i * nn + j * nn * nx + 2] / 255.0f;
		//std::cout << r << ' ' << g << ' ' << b << std::endl;
		return vec3(r, g, b);
	}
};