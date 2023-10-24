#pragma once
#include<string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;

	unsigned int ID;// Shader program ID
};

