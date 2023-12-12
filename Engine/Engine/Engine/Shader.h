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
	std::string geometryString;
	const char* vertexSource;
	const char* fragmentSource;
	const char* geometrySource;
	unsigned int ID;// Shader program ID

	enum slot
	{
		DIFFUSE,
		SPECULAR
	};

	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

	void Use() const;

	void SetUniform1i(const char* paramNameString, unsigned int  value) const;
	void SetUniform1f(const char* paramNameString, float value) const;
	void SetUniform2f(const char* paramNameString, float x, float y) const;
	void SetUniform2fv(const char* paramNameString, const glm::vec2& value) const;
	void SetUniform3f(const char* paramNameString, float x ,float y ,float z) const;
	void SetUniform3fv(const char* paramNameString, const glm::vec3& value) const;
	void SetUniform4f(const char* paramNameString, float x, float y, float z,float w) const;
	void SetUniform4fv(const char* paramNameString, glm::vec4& value) const;
	void SetUniformMatrix2fv(const char* paramNameString, const glm::mat2& value) const;
	void SetUniformMatrix3fv(const char* paramNameString, const glm::mat3& value) const;
	void SetUniformMatrix4fv(const char* paramNameString, const glm::mat4& value) const;


private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

