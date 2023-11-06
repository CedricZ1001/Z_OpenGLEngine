#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp):mouseSensitivity(0.01){
	this->position = position;
	this->worldUp = worldUp;
	this->forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(forward, right));
	//up = worldUp;
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp):mouseSensitivity(0.01){
	this->position = position;
	this->worldUp = worldUp;
	this->pitch = pitch;
	this->yaw = yaw;
	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = -glm::cos(pitch) * glm::cos(yaw);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(forward, right));
}

glm::mat4 Camera::GetViewMatrix(){
	return glm::lookAt(position, position + forward, worldUp);
}

void Camera::UpdateCameraVector(){
	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = -glm::cos(pitch) * glm::cos(yaw);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(forward, right));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	pitch += deltaX * mouseSensitivity;
	yaw -= deltaY * mouseSensitivity;
	UpdateCameraVector();
}

void Camera::SetSensortivity(float sensitivity = 0.01){
	mouseSensitivity = sensitivity;
}