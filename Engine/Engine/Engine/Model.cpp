#include "Model.h"

Model::Model(const string& path){
	LoadModel(path);
}

void Model::LoadModel(const string& path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "Assimp error" << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('\\'));
	cout << "Success!" + directory << endl;
}
