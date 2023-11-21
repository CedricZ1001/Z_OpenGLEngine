#include "Mesh.h"

Mesh::Mesh(float _vertices[])
{
	vertices.resize(36);
	memcpy(&vertices[0], _vertices, 36 * 8 * sizeof(float));
	stepMesh();
}

Mesh::Mesh(vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures) :
	vertices(_vertices),
	indices(_indices),
	textures(_textures){

	stepMesh();
}

void Mesh::Draw(Shader* shader){
	for  (auto item : textures){
		if (item.type=="texture_diffuse"){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, item.id);
			shader->SetUniform1f("material.diffuse", 0);
		}
		else if (item.type == "specular_diffuse") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, item.id);
			shader->SetUniform1f("material.specular", 1);
		}
	}
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::stepMesh(){

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
}
