#include "Material.h"

Material::Material(Shader* _shader, glm::vec3 _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess) : 
	shader(_shader),
	diffuse(_diffuse),
	ambient(_ambient),
	specular(_specular),
	shininess(_shininess)
{
}

Material::Material(Shader* _shader, unsigned int _diffuse, glm::vec3 _ambient, glm::vec3 _specular, float _shininess) :
	shader(_shader),
	diffuseTexture(_diffuse),
	ambient(_ambient),
	specular(_specular),
	shininess(_shininess)
{
}
