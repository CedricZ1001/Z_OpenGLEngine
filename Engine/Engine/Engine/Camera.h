#pragma once
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;
	float pitch;
	float yaw;
	double mouseSensitivity;


	Camera(glm::vec3 position,glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
	glm::mat4 GetViewMatrix();
	void SetSensortivity(double sensitivity);
	void ProcessMouseMovement(float deltaX, float deltaY);
private:
	void UpdateCameraVector();
	
	
	
};

