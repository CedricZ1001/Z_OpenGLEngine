#pragma once
#include<iostream>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<vector>
#include"Shader.h"

using std::string, std::vector;
#define MAX_BONE_INFLUENCE 4
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh{
public:
	
	vector<Vertex>		 vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;
	unsigned int VAO;

	Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures);
	Mesh(float _vertices[]);

	void Draw(Shader& shader);

private:
	unsigned int VBO, EBO;
	void StepMesh();

};

