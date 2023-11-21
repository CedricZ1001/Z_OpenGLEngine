#pragma once
#include<iostream>
#include<vector>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include <fstream>
#include <sstream>
#include"Mesh.h"
#include"Shader.h"
using std::vector, std::cout, std::endl;

class Model
{
public:
	vector<Mesh> meshes;
	string directory;

	Model(const string &path);
	void Draw(Shader* shader);

private:
	void LoadModel(const string& path);
	void ProcessNode(aiNode* node,const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

