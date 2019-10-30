#ifndef RANDOMH
#define RANDOMH

#include <cstdlib>

inline float random_float() 
{
	return rand() / (RAND_MAX + 1.0f);
}

#endif