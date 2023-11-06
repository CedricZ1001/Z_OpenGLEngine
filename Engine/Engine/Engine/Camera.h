#pragma once
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;
	float pitch;
	float yaw;
	float mouseSensitivity;

	glm::mat4 GetViewMatrix();
	void SetSensortivity(float sensitivity);

private:
	void UpdateCameraVector();
	void ProcessMouseMovement(float deltaX,float deltaY);
	
};

