#pragma once
#include<string>
#include <GL/glew.h>

class Shader
{
public:
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;// Shader program ID

	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

