#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	uint32_t ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	
	void use();

	void setValue(const std::string& name, bool value) const;
	void setValue(const std::string& name, int value) const;
	void setValue(const std::string& name, float value) const;
};