#include "LightDirectional.h"

LightDirectional::LightDirectional( glm::vec3 _angles, glm::vec3 _color):
angles(_angles),
color(_color){
	UpdateDirection();
}

 
void LightDirectional::UpdateDirection(){
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}
