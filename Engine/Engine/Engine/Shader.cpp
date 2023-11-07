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

void Shader::Use(){
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char* paramNameString, glm::vec3 param){
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);
}

void Shader::SetUniformMatrix4fv(const char* paramNameString, glm::mat4 param){
	glUniformMatrix4fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, glm::value_ptr(param));
}

void Shader::SetUniform1f(const char* paramNameString, float param){
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::SetUniform1i(const char* paramNameString, unsigned int param){
	glUniform1i(glGetUniformLocation(ID, paramNameString), param);
}



