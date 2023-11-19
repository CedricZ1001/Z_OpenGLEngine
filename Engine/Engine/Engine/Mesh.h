#pragma once
#include<iostream>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<vector>
#include"Shader.h"

using std::string, std::vector;
class Mesh
{
public:
	struct Vertex{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct Texture{
		unsigned int id;
		string type;
		string path;
	};

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures);

	void Draw(Shader* shader);

private:
	unsigned int VBO, VAO, EBO;
	void stepMesh();

};

