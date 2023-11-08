#pragma once
#include<string>
#include <GL/glew.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

class Shader
{
public:
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;// Shader program ID

	enum slot
	{
		DIFFUSE,
		SPECULAR
	};

	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	void SetUniform3f(const char* paramNameString, glm::vec3 param);
	void SetUniformMatrix4fv(const char* paramNameString, glm::mat4 param);
	void SetUniform1f(const char* paramNameString, float param);
	void SetUniform1i(const char* paramNameString, unsigned int  param);

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

