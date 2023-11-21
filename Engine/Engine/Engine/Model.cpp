#include "Model.h"

Model::Model(const string& path){
	LoadModel(path);
	
}

void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); ++i)
	{
		meshes[i].Draw(shader);
	}
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
	//cout << "Success!" + directory << endl;
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node,const aiScene* scene){
	cout << node->mName.data << endl;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(curMesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> tempVertices;
	vector<unsigned int> tempIndices;
	vector<Texture> tempTexture;

	glm::vec3 tempvector;
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i){
		Vertex tempVertex;

		tempVertex.position.x = mesh->mVertices[i].x;
		tempVertex.position.y = mesh->mVertices[i].y;
		tempVertex.position.z = mesh->mVertices[i].z;


		tempVertex.normal.x = mesh->mNormals[i].x;
		tempVertex.normal.y = mesh->mNormals[i].y;

		tempVertex.normal.z = mesh->mNormals[i].z;
		if (mesh->mTextureCoords[0]){
			tempVertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			tempVertex.texCoords = glm::vec2(0, 0);
		}
		tempVertices.push_back(tempVertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
		{
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	
	return Mesh(tempVertices, tempIndices, {});
}
