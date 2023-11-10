#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>

//using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;
	

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);


	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("open file error!");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//printf(vertexSource);
		//printf(fragmentSource);
	}
	catch (const std::exception& e)
	{
		printf(e.what());
	}
	//init Shader
	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type){
	int success;
	char infoLog[512];
	if (type != "PROGRAM"){
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader compile error: " << infoLog << std::endl;
		}
	}
	else{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success){
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader link error: " << infoLog << std::endl;
		}
	}
}

void Shader::Use() const{
	glUseProgram(ID);
}


void Shader::SetUniform1i(const char* paramNameString, unsigned int value) const {
	glUniform1i(glGetUniformLocation(ID, paramNameString), value);
}

void Shader::SetUniform1f(const char* paramNameString, float value) const{
	glUniform1f(glGetUniformLocation(ID, paramNameString), value);
}

void Shader::SetUniform2f(const char* paramNameString, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, paramNameString), x, y);
}

void Shader::SetUniform2fv(const char* paramNameString, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, paramNameString), 1, &value[0]);
}

void Shader::SetUniform3f(const char* paramNameString, float x, float y, float z) const{
	glUniform3f(glGetUniformLocation(ID, paramNameString), x, y, z);
}

void Shader::SetUniform3fv(const char* paramNameString, const glm::vec3 &value) const{
	glUniform3fv(glGetUniformLocation(ID, paramNameString), 1, &value[0]);
}

void Shader::SetUniform4f(const char* paramNameString, float x, float y, float z, float w) const{
	glUniform4f(glGetUniformLocation(ID, paramNameString), x, y, z, w);
}

void Shader::SetUniform4fv(const char* paramNameString, glm::vec4& value) const{
	glUniform4fv(glGetUniformLocation(ID, paramNameString), 1, &value[0]);
}

void Shader::SetUniformMatrix2fv(const char* paramNameString, const glm::mat2 &value) const{
	glUniformMatrix2fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMatrix3fv(const char* paramNameString, const glm::mat3 &value) const{
	glUniformMatrix3fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetUniformMatrix4fv(const char* paramNameString, const glm::mat4 &value) const{
	glUniformMatrix4fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, &value[0][0]);
}





