#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<filesystem>
#include"Shader.h"
#include"Loadimg.h"
#include"Camera.h"
#include"Material.h"
#include"LightDirectional.h"
#include"LightPoint.h"
#include"LightSpot.h"
#include"Mesh.h"
#include"Model.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#pragma region Config
// Screen
const unsigned int SCR_WIDTH = 1980;
const unsigned int SCR_HEIGHT = 1080;

// Input
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool isFirstMouse = true;
bool handleMouseMovement = false;

//time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void DrawDirLight(Shader* shader, glm::vec3 lightPos, glm::vec3 lightColor, unsigned int cubeVAO);
void DrawBasicBox(Shader* shader,glm::vec3 position, glm::vec3 objectColor, glm::vec3 lightColor, unsigned int cubeVAO);
void DrawPhongBox(Shader* shader, glm::vec3 position, glm::vec3 objectColor, glm::vec3 lightPos, glm::vec3 lightColor, unsigned int cubeVAO);
void DrawTextureBox(Shader* shader, glm::vec3 position, glm::vec3 lightPos, glm::vec3 lightColor, unsigned int cubeVAO, unsigned int diffuse, unsigned int specular);
unsigned int loadTexture(char const* path);
void DrawModel(Shader* shader, glm::vec3 position, glm::vec3 lightPos, glm::vec3 lightColor, Model model);

#pragma endregion

#pragma region Model data
GLfloat vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(20.0f,  5.0f, -15.0f),
	  glm::vec3(-20.5f, -2.2f, -2.5f),
	  glm::vec3(-15.8f, -2.0f, -12.3f),
	  glm::vec3(15.4f, -0.4f, -3.5f),
	  glm::vec3(-10.7f,  3.0f, -7.5f),
	  glm::vec3(10.3f, -2.0f, -2.5f),
	  glm::vec3(-5.5f,  2.0f, -2.5f),
	  glm::vec3(5.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -20.5f)
};



float cubeVertices[] = {
	// positions          // normals
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

float transparentVertices[] = {
	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};


float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};
//����
float points[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // ����
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // ����
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // ����
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // ����
};

vector<glm::vec3> vegetation{
	glm::vec3(-5.0f, 0.0f, -0.48f),
	glm::vec3(5.0f, 0.0f, 0.51f),
	glm::vec3(0.0f, 0.0f, 0.7f),
	glm::vec3(-2.5f, 0.0f, -2.3f),
	glm::vec3(2.5f, 0.0f, -0.6f)
};

#pragma endregion

#pragma region Light Declare

LightDirectional* light = new LightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), 0, 0));

//LightPoint* light = new LightPoint(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), 0, 0));

//LightSpot* light = new LightSpot(
//	glm::vec3(0.0f, 0.0f, 5.0f),
//	glm::vec3(0, 0, -1), 
//	glm::vec3(0.5f, 0.5f, 0.5f),
//	glm::vec3(0.8f, 0.8f, 0.8f),
//	glm::vec3(1.0f, 1.0f, 1.0f));

#pragma endregion

#pragma region Camera Declare
//init camera
//Camera* mycamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
Camera* mycamera = new Camera(glm::vec3(3, 3, 15.0f));
#pragma endregion

#pragma region Input Declare

void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn) {

	if (!handleMouseMovement) {
		return;
	}
	float xPos = static_cast<float>(xPosIn);
	float yPos = static_cast<float>(yPosIn);

	if (isFirstMouse) {
		lastX = xPos;
		lastY = yPos;
		isFirstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	mycamera->ProcessMouseMovement(xOffset, yOffset);
}

void ProcessInput(GLFWwindow* window) { 
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
		handleMouseMovement = false;
		isFirstMouse = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		handleMouseMovement = true;
	}
	 

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mycamera->ProcessKeyboard(FORWARD, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mycamera->ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mycamera->ProcessKeyboard(LEFT, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mycamera->ProcessKeyboard(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		mycamera->ProcessKeyboard(LIFT, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mycamera->ProcessKeyboard(DOWN, deltaTime);
	}
}



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mycamera->ProcessMouseScroll(static_cast<float>(yoffset));
}

#pragma endregion

#pragma region framebuffer_size_callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
#pragma endregion

#pragma region loadCubeMap

unsigned int LoadCubeMap(vector<std::string>& faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
#pragma endregion


int main(int argc, char* argv[]) {

#pragma region Open Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);//4xMSAA
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// on MacOS  you need to add
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MY OpenGL Game", NULL, NULL);

	// Open GLFW window
	if (window == NULL) {
		printf("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//Init GLEW
	//glewExperimental = true; 
	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); 

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

#pragma endregion

#pragma region Load IMG
//load img
	//Loadimg* awesome = new Loadimg("assets/Material/Texture/awesomeface.png", GL_RGBA, GL_RGBA);
	//Loadimg* container = new Loadimg("assets/Material/Texture/container.png", GL_RGBA, GL_RGBA);
	//Loadimg* container_specular = new Loadimg("assets/Material/Texture/container_specular.png", GL_RGBA, GL_RGBA);
	unsigned int container = loadTexture("assets/Material/Texture/container.png");
	unsigned int container_specular = loadTexture("assets/Material/Texture/container_specular.png");

	cout << container << endl;
	cout << container_specular<< endl;
#pragma endregion

#pragma region Init VBO and VAO

	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));




	// UBO set uniform 
	GLuint uboMatrices;
	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


#pragma endregion

#pragma region Init Shader
	//init shader
	Shader* cubeLight = new Shader("assets/Material/Shader/cubeLight.vert", "assets/Material/Shader/cubeLight.frag");
	Shader* basicLightShader = new Shader("assets/Material/Shader/basicLight.vert", "assets/Material/Shader/basicLight.frag");
	Shader* PhongShader = new Shader("assets/Material/Shader/Phong.vert", "assets/Material/Shader/Phong.frag");
	Shader* PointLightShader = new Shader("assets/Material/Shader/PointLight.vert", "assets/Material/Shader/PointLight.frag");
	Shader* ModelShader = new Shader("assets/Material/Shader/Model_loading.vert", "assets/Material/Shader/Model_loading.frag");

	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboMatrices);

#pragma endregion

#pragma region Init Material
	//Material* myMaterial = new Material(myshader,
	//	glm::vec3(0.7f, 0.5f, 0.3f),
	//	glm::vec3(0.3f, 0.2f, 0.2f),
	//	glm::vec3(1.0f, 1.0f, 1.0f),
	//	64);

	//Material* containerMaterial = new Material(myshader,
	//	container->TexBuffer,
	//	glm::vec3(1.0f, 1.0f, 1.0f),
	//	container_specular->TexBuffer,
	//	64);

#pragma endregion

#pragma region Perpare before rendering
//model mat
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;

	glm::vec3 lightPos;
	glm::vec3 lightColor(1.0f);
	float light_pos_value = 0;
	float radius = 5.0f; // 光源旋转半径
	float lightAngle = light_pos_value; // 使用时间作为旋转角度

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 420");
	bool isLightCircularMotion = true;
	bool isDrawDirLight = true;
	bool isDrawBasicBox = true;
	bool isDrawPhongBox = true;
	bool isDrawTextureBox = true;
	bool isDrawNanosuit = true;

	glm::vec3 lastDirlightColor(1.0f);
	glm::vec3 basicBoxColor(1.0f, 0.5f, 0.31f);
	glm::vec3 phongBoxColor(1.0f, 0.5f, 0.31f);

	glm::vec3 phongBoxPosition(2.0f, 0.0f, 0.0f);
	glm::vec3 basicBoxPosition(0.0f, 0.0f, 0.0f);
	glm::vec3 textureBoxPosition(-2.0f, 0.0f, 0.0f);
	glm::vec3 NanosuitPosition(5.0f, -1.0f, 0.0f);

	std::filesystem::path exePath = argv[0];
	string path = exePath.parent_path().parent_path().parent_path().string() + "\\Engine\\assets\\Model\\nanosuit\\nanosuit.obj";
	Model Nanosuit(path);

	path = exePath.parent_path().parent_path().parent_path().string() + "\\Engine\\assets\\Model\\planet\\planet.obj";
	Model planet(path);

	//uniform����
	//cout << GL_MAX_VERTEX_UNIFORM_COMPONENTS << endl; //35658
	//cout << GL_MAX_FRAGMENT_UNIFORM_COMPONENTS << endl; //35657
	// 
	//unifrom��С����
	//cout << GL_MAX_UNIFORM_BLOCK_SIZE << endl; //35376

#pragma endregion


#pragma region Render Loop
	while (!glfwWindowShouldClose(window)) {

		// per-frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		//cout << 1 / deltaTime << endl;
		lastFrame = currentFrame;
		
		
		if (isLightCircularMotion) {
			lightAngle = currentFrame;// 使用时间作为旋转角度
		}
		else {
			lightAngle = light_pos_value;
		}
		lightPos.x = sin(lightAngle) * radius;
		lightPos.y = 1.0f; // 如果你想在y轴上旋转，保持y坐标不变
		lightPos.z = cos(lightAngle) * radius;

		// ProcessInput
		ProcessInput(window);
		// Clear Screen
		//glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.
		
		//bind UBO 
		viewMat = mycamera->GetViewMatrix();
		projMat = glm::perspective(glm::radians(mycamera->zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(viewMat));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projMat));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		//light
		if (!isDrawDirLight) {
			lightColor = glm::vec3(0.0f);
		}
		else{
			lightColor = lastDirlightColor;
			DrawDirLight(cubeLight, lightPos, lightColor, cubeVAO);
		}

		//model
		if (isDrawBasicBox) {
			DrawBasicBox(basicLightShader, basicBoxPosition, basicBoxColor, lightColor, cubeVAO);
		}
		if (isDrawPhongBox) {
			DrawPhongBox(PhongShader, phongBoxPosition, phongBoxColor, lightPos, lightColor, cubeVAO);
		}
		if (isDrawTextureBox) {
			DrawTextureBox(PointLightShader, textureBoxPosition, lightPos, lightColor, cubeVAO, container, container_specular);
		}
		if (isDrawNanosuit) {
			DrawModel(ModelShader, NanosuitPosition, lightPos, lightColor, Nanosuit);
		}
		

		//ImGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Customize setting");
		if (ImGui::TreeNode("Light")) {
			if (ImGui::TreeNode("DirectionLight")) { // 可展开的分组
				ImGui::Checkbox("Draw Directional Light", &isDrawDirLight);
				ImGui::Checkbox("circular motion", &isLightCircularMotion);
				ImGui::SliderFloat("Light Position", &light_pos_value, 0.0f, 6.28f);
				ImGui::ColorEdit3("Light Color", (float*)&lastDirlightColor);
				ImGui::TreePop(); // 结束分组
			}
			ImGui::TreePop(); // 结束分组
		}
		if (ImGui::TreeNode("Model")) {
			if (ImGui::TreeNode("BasicBox")) {
				ImGui::Checkbox("Draw BasicBox", &isDrawBasicBox);
				ImGui::ColorEdit3("Color", (float*)&basicBoxColor);
				ImGui::SliderFloat3("position", (float*)&basicBoxPosition, -20.0f, 20.0f, "%.1f");
				ImGui::TreePop(); // 结束分组
			}
			if (ImGui::TreeNode("PhongBox")) {
				ImGui::Checkbox("Draw PhongBox", &isDrawPhongBox);
				ImGui::ColorEdit3("Color", (float*)&phongBoxColor);
				ImGui::SliderFloat3("position", (float*)&phongBoxPosition, -20.0f, 20.0f, "%.1f");
				ImGui::TreePop(); // 结束分组
			}
			if (ImGui::TreeNode("TextureBox")) {
				ImGui::Checkbox("Draw PhongBox", &isDrawTextureBox);
				ImGui::SliderFloat3("position", (float*)&textureBoxPosition, -20.0f, 20.0f, "%.1f");
				ImGui::TreePop(); // 结束分组
			}
			if (ImGui::TreeNode("Nanosuit")) {
				ImGui::Checkbox("Draw Nanosuit", &isDrawNanosuit);
				ImGui::SliderFloat3("position", (float*)&NanosuitPosition, -20.0f, 20.0f, "%.1f");
				ImGui::TreePop(); // 结束分组
			}
			ImGui::TreePop();
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Clean up, prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

#pragma region Exit Program
	// Exit Program
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
#pragma endregion

}

void DrawDirLight(Shader* shader, glm::vec3 lightPos, glm::vec3 lightColor, unsigned int cubeVAO) {

	shader->Use();
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, lightPos);
	modelMat = glm::scale(modelMat, glm::vec3(0.3f));
	shader->SetUniformMatrix4fv("model", modelMat);
	shader->SetUniform3fv("lightColor", lightColor);
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void DrawBasicBox(Shader* shader, glm::vec3 position, glm::vec3 objectColor, glm::vec3 lightColor, unsigned int cubeVAO) {

	shader->Use();
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, position);
	shader->SetUniformMatrix4fv("model", modelMat);
	shader->SetUniform3fv("objectColor", objectColor);
	shader->SetUniform3fv("lightColor", lightColor);
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void DrawPhongBox(Shader* shader, glm::vec3 position, glm::vec3 objectColor, glm::vec3 lightPos, glm::vec3 lightColor, unsigned int cubeVAO) {
	shader->Use();
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, position);
	shader->SetUniformMatrix4fv("model", modelMat);
	shader->SetUniform3fv("objectColor", objectColor);
	shader->SetUniform3fv("lightColor", lightColor);
	shader->SetUniform3fv("lightPos", lightPos);
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void DrawTextureBox(Shader* shader, glm::vec3 position, glm::vec3 lightPos, glm::vec3 lightColor, unsigned int cubeVAO, unsigned int diffuse, unsigned int specular) {
	shader->Use();
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, position);
	shader->SetUniformMatrix4fv("modelMat", modelMat);
	shader->SetUniform1i("material.diffuse", 0);
	shader->SetUniform1i("material.specular", 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular);
	shader->SetUniform1f("material.shininess", 64.0f);

	shader->SetUniform1f("pointLight.constant", 1.0f);
	shader->SetUniform1f("pointLight.linear", 0.09f);
	shader->SetUniform1f("pointLight.quadratic", 0.032f);

	shader->SetUniform3fv("pointLight.color", lightColor);
	shader->SetUniform3fv("pointLight.ambient", glm::vec3(0.2f));
	shader->SetUniform3fv("pointLight.diffuse", glm::vec3(0.8f));
	shader->SetUniform3fv("pointLight.specular", glm::vec3(1.0f));
	shader->SetUniform3fv("pointLight.position", lightPos);

	shader->SetUniform3fv("viewPos", mycamera->position);
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void DrawModel(Shader* shader, glm::vec3 position, glm::vec3 lightPos, glm::vec3 lightColor,Model model) {
	shader->Use();
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, position);
	shader->SetUniformMatrix4fv("model", modelMat);
	shader->SetUniform1f("material.shininess", 64.0f);

	shader->SetUniform1f("pointLight.constant", 1.0f);
	shader->SetUniform1f("pointLight.linear", 0.09f);
	shader->SetUniform1f("pointLight.quadratic", 0.032f);

	shader->SetUniform3fv("light.color", lightColor);
	shader->SetUniform3fv("light.ambient", glm::vec3(0.2f));
	shader->SetUniform3fv("light.diffuse", glm::vec3(0.8f));
	shader->SetUniform3fv("light.specular", glm::vec3(1.0f));
	shader->SetUniform3fv("light.position", lightPos);
	shader->SetUniform3fv("viewPos", mycamera->position);

	model.Draw(*shader);

}

unsigned int loadTexture(char const* path){
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}