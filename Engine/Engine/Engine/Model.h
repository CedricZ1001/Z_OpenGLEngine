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
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	Model(const string& path, bool gamma = false);
	void Draw(Shader& shader);

private:
	void LoadModel(const string& path);
	void ProcessNode(aiNode* node,const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);

};

