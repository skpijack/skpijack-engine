#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>


class Texture {
public:
	uint32_t texture;
	
	Texture(std::string texture_path);
	void bind();
	void bind(GLenum index);
};