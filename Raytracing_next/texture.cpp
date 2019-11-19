#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"


image_texture::image_texture(const char* dataPath)
{
	_data = stbi_load(dataPath, &nx, &ny, &nn, 0);
	std::cout << nx << ' ' << ny << ' ' << nn << std::endl;
	if (_data == NULL)
	{
		std::cerr << "load image error";
	}
}