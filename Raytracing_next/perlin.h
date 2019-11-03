#pragma once
#include "vec3.h"
#include "random.h"
#include <math.h>

inline float perlin_interp(vec3 gradient[2][2][2], float u, float v, float w)
{
	float uu = u * u * (3 - 2 * u);
	float vv = v * v * (3 - 2 * v);
	float ww = w * w * (3 - 2 * w);
	float result = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				vec3 weight_vec = vec3(u - i, v - j, w - k);
				result += (i * uu + (1 - i) * (1 - uu)) * 
					(j * vv + (1 - j) * (1 - vv)) *
					(k * ww + (1 - k) * (1 - ww)) * dot(gradient[i][j][k], weight_vec);
			}
		}
	}
	return result;
}

class perlin
{
private :
	static vec3* randomvec;
	static int* perm_x;
	static int* perm_y;
	static int* perm_z;
public :
	float noise(const vec3& point) const
	{
		float u = point.x() - floor(point.x());
		float v = point.y() - floor(point.y());
		float w = point.z() - floor(point.z());
		int i = floor(point.x());
		int j = floor(point.y());
		int k = floor(point.z());
		vec3 gradient[2][2][2];
		for (int gi = 0; gi < 2; gi++)
		{
			for (int gj = 0; gj < 2; gj++)
			{
				for (int gk = 0; gk < 2; gk++)
				{
					gradient[gi][gj][gk] = randomvec[perm_x[(i + gi) & 255] ^ perm_y[(j + gj) & 255] ^ perm_z[(k + gk) & 255]];
				}
			}
		}
		return perlin_interp(gradient, u, v, w);
	}

	float turbulence(const vec3& point, int depth = 7) const
	{
		float result = 0.0f;
		float weight = 1.0f;
		vec3 temp = point;
		for (int i = 0; i < depth; i++)
		{
			result += weight * noise(temp);
			weight *= 0.5f;
			temp *= 2.0f;
		}
		return fabs(result);
	}
};

static vec3* perlin_generate()
{
	vec3* p = new vec3[256];
	for (int i = 0; i < 256; ++i)
	{
		float x = 2.0f * random_float() - 1.0f;
		float y = 2.0f * random_float() - 1.0f;
		float z = 2.0f * random_float() - 1.0f;
		p[i] = normalized_vector(vec3(x, y, z));
	}
	return p;
}

void permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = int(random_float() * (i + 1));
		int temp = p[target];
		p[target] = p[i];
		p[i] = temp;
	}
}

static int* perlin_generate_perm()
{
	int* perm = new int[256];
	for (int i = 0; i < 256; i++)
	{
		perm[i] = i;
	}
	permute(perm, 256);
	return perm;
}

vec3* perlin::randomvec = perlin_generate();
int* perlin::perm_x = perlin_generate_perm();
int* perlin::perm_y = perlin_generate_perm();
int* perlin::perm_z = perlin_generate_perm();