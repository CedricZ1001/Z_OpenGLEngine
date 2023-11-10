#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular):
	position(_position),
	angles(_angles),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular)
	{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

void LightSpot::UpdateDirection(){
	direction = glm::vec3(0, 0, -1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
}
