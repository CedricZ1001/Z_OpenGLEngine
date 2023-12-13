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


#pragma region Config
// Screen
const unsigned int SCR_WIDTH = 1980;
const unsigned int SCR_HEIGHT = 1080;

// Input
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool isFirstMouse = true;

//time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
//顶点
float points[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
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
Camera* mycamera = new Camera(glm::vec3(0, 0, 3.0f));
#pragma endregion

#pragma region Input Declare

void ProcessInput(GLFWwindow* window ) { //输入检测
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

void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn) {

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
unsigned int LoadCubeMap(vector<std::string> &faces)
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);//3.3开始使用可编程渲染管线
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//早期固定流水线，现在可编程化流水线一般都使用GLFW_OPENGL_CORE_PROFILE，另一个配置GLFW_OPENGL_COMPAT_PROFILE可以使用过时的特性和固定流水线
	
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
	//glewExperimental = true; //实验性模式
	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize GLEW");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); //设置视口(Viewport)的大小 及定义屏幕上绘制图形的位置和大小

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_BLEND);//混合模式
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_PROGRAM_POINT_SIZE);//启用顶点图元
#pragma endregion

	#pragma region Load IMG
	//load img
	Loadimg* awesome = new Loadimg("assets/Material/Texture/awesomeface.png",GL_RGBA, GL_RGBA);
	//Loadimg* container = new Loadimg("assets/Material/Texture/container.png", GL_RGBA, GL_RGBA);
	//Loadimg* container_specular = new Loadimg("assets/Material/Texture/container_specular.png", GL_RGBA, GL_RGBA);
	

#pragma endregion
	
	#pragma region Init VBO and VAO
	//Mesh cube(vertices);
	std::filesystem::path exePath = argv[0];
	string path = exePath.parent_path().parent_path().parent_path().string() + "\\Engine\\assets\\Model\\nanosuit\\nanosuit.obj";
	/*cout << path << endl;*/
	Model model(path);
	path = exePath.parent_path().parent_path().parent_path().string() + "\\Engine\\assets\\Model\\planet\\planet.obj";
	Model planet(path);

	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	unsigned int transparentVAO, transparentVBO;
	glGenVertexArrays(1, &transparentVAO);
	glGenBuffers(1, &transparentVBO);
	glBindVertexArray(transparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);


	// screen quad VAO
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	Loadimg* transparentTex = new Loadimg("assets/Material/Texture/grass.png", GL_RGBA, GL_RGBA);

	unsigned int FBO,texColorBuffer,RBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// UBO set uniform 
	GLuint uboMatrices;
	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


	//test VAO VBO
	unsigned int testVAO, testVBO;
	glGenVertexArrays(1, &testVAO);
	glGenBuffers(1, &testVBO);
	glBindVertexArray(testVAO);
	glBindBuffer(GL_ARRAY_BUFFER, testVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));

	


	vector<std::string> faces
	{
		"assets/Material/Texture/skybox/right.jpg",
		"assets/Material/Texture/skybox/left.jpg",
		"assets/Material/Texture/skybox/top.jpg",
		"assets/Material/Texture/skybox/bottom.jpg",
		"assets/Material/Texture/skybox/front.jpg",
		"assets/Material/Texture/skybox/back.jpg"
	};

	unsigned int cubemapTexture = LoadCubeMap(faces);
	//立方体贴图
	//unsigned int CubeTex;
	//glGenTextures(1, &CubeTex);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, CubeTex);

	// 生成纹理
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	// 将它附加到当前绑定的帧缓冲对象
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#pragma endregion

	#pragma region Init Shader
	//init shader
	//Shader* myshader = new Shader("assets/Material/Shader/SpotLight.vert", "assets/Material/Shader/SpotLight.frag");
	//Shader* myshader = new Shader("assets/Material/Shader/explode.vert", "assets/Material/Shader/explode.frag", "assets/Material/Shader/explode.geom");
	Shader* myshader = new Shader("assets/Material/Shader/Model_loading.vert", "assets/Material/Shader/Model_loading.frag");
	Shader* normalShader = new Shader("assets/Material/Shader/normal_visualization.vert", "assets/Material/Shader/normal_visualization.frag","assets/Material/Shader/normal_visualization.geom");
	Shader* planetShader = new Shader("assets/Material/Shader/planet.vert", "assets/Material/Shader/planet.frag");
	//Shader* shaderSingleColor = new Shader("assets/Material/Shader/stencil_testing.vert", "assets/Material/Shader/stencil_testing.frag");
	Shader* grassShader = new Shader("assets/Material/Shader/vegetation.vert", "assets/Material/Shader/vegetation.frag");
	Shader* screenShader = new Shader("assets/Material/Shader/frameBuffer.vert", "assets/Material/Shader/frameBuffer.frag");
	Shader* skyboxShader = new Shader("assets/Material/Shader/skybox.vert", "assets/Material/Shader/skybox.frag");
	Shader* cubeShader = new Shader("assets/Material/Shader/cubeMap.vert", "assets/Material/Shader/cubeMap.frag");
	//Shader* testShader = new Shader("assets/Material/Shader/vertex.vert", "assets/Material/Shader/fragment.frag", "assets/Material/Shader/geometry.geom");


	//GLuint blockIndex = glGetUniformBlockIndex(cubeShader->ID, "Matrices");
	//glUniformBlockBinding(cubeShader->ID, blockIndex, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboMatrices);

	screenShader->SetUniform1i("screenTexture", 0);
	cubeShader->SetUniform1i("screenTexture", 0);

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

	#pragma region Perpare MVP
	//model mat
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;

	//uniform数量
	//cout << GL_MAX_VERTEX_UNIFORM_COMPONENTS << endl; //35658
	//cout << GL_MAX_FRAGMENT_UNIFORM_COMPONENTS << endl; //35657
	// 
	//unifrom大小限制
	//cout << GL_MAX_UNIFORM_BLOCK_SIZE << endl; //35376
	unsigned int amount = 2000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // 初始化随机种子    
	float radius = 50.0;
	float offset = 2.5f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 planetModelMat(1.0f);
		// 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // 让行星带的高度比x和z的宽度要小
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		planetModelMat = glm::translate(planetModelMat, glm::vec3(x, y, z));

		// 2. 缩放：在 0.05 和 0.25f 之间缩放
		float scale = (rand() % 20) / 100.0f + 0.05;
		planetModelMat = glm::scale(planetModelMat, glm::vec3(scale));

		// 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
		float rotAngle = (rand() % 360);
		planetModelMat = glm::rotate(planetModelMat, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. 添加到矩阵的数组中
		modelMatrices[i] = planetModelMat;
	}
#pragma endregion

	#pragma region Render Loop
	while (!glfwWindowShouldClose(window)) {
		
		// per-frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		cout << 1 / deltaTime << endl;
		lastFrame = currentFrame;

		// ProcessInput
		ProcessInput(window);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glEnable(GL_DEPTH_TEST);
		// Clear Screen
		//glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.

		/*testShader->Use();
		glBindVertexArray(testVAO);
		glDrawArrays(GL_POINTS, 0, 4);*/

		// Shader Program
		myshader->Use();
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilMask(0xFF);

		// Set MVPMatrixs
		modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat,glm::vec3(0, -10, 0));
		viewMat = mycamera->GetViewMatrix();
		projMat = glm::perspective(glm::radians(mycamera->zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(viewMat));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projMat));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		// Uniform
		myshader->SetUniformMatrix4fv("model", modelMat);
		myshader->SetUniform1f("time", glfwGetTime());

		myshader->SetUniform3fv("dirLight.direction", mycamera->forward);
		myshader->SetUniform3fv("dirLight.ambient", glm::vec3(0.2, 0.2, 0.2));
		myshader->SetUniform3fv("dirLight.diffuse", glm::vec3(0.8, 0.8, 0.8));
		myshader->SetUniform3fv("dirLight.specular", glm::vec3(1, 1, 1));
		model.Draw(*myshader);
		myshader->SetUniform3fv("dirLight.viewPos", mycamera->position);
		normalShader->Use();
		normalShader->SetUniformMatrix4fv("model", modelMat);
		model.Draw(*normalShader);
		// Set Model
		//glBindVertexArray(VAO);
		
		// DrawCall
		
		planetShader->Use();
		glm::mat4 planetModelMat(1.0f);
		planetModelMat = glm::translate(planetModelMat, glm::vec3(18.0f, -3.0f, 0.0f));
		planetModelMat = glm::scale(planetModelMat, glm::vec3(4.0f, 4.0f, 4.0f));
		planetShader->SetUniformMatrix4fv("model", planetModelMat);
		planet.Draw(*planetShader);
		for (unsigned int i = 0; i < amount; i++)
		{
			planetShader->SetUniformMatrix4fv("model", modelMatrices[i]);
			planet.Draw(*planetShader);
		}
		
		
		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilMask(0x00); // 禁止模板缓冲的写入
		//glDisable(GL_DEPTH_TEST);
		//shaderSingleColor->Use();

		//modelMat = glm::mat4(1.0f);
		//modelMat = glm::scale(modelMat, glm::vec3(1.005, 1.005, 1.005));
		//viewMat = mycamera->GetViewMatrix();
		//projMat = glm::perspective(glm::radians(mycamera->zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		//// Uniform
		//shaderSingleColor->SetUniformMatrix4fv("model", modelMat);
		//shaderSingleColor->SetUniformMatrix4fv("view", viewMat);
		//shaderSingleColor->SetUniformMatrix4fv("projection", projMat);
		//model.Draw(*shaderSingleColor);
		//glStencilMask(0xFF);
		//glStencilFunc(GL_ALWAYS, 0, 0xFF);
		//glEnable(GL_DEPTH_TEST);

		// cubes
		cubeShader->Use();
		modelMat = glm::translate(modelMat, glm::vec3(4.0, 4.0, 0));
		cubeShader->SetUniformMatrix4fv("model", modelMat);
		//cubeShader->SetUniformMatrix4fv("view", viewMat);
		//cubeShader->SetUniformMatrix4fv("projection", projMat);

		cubeShader->SetUniform3fv("cameraPos", mycamera->position);
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		grassShader->Use();
		glBindVertexArray(transparentVAO);
		glBindTexture(GL_TEXTURE_2D, transparentTex->TexBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, glm::vec3(0, -9, 0));
			modelMat = glm::translate(modelMat, vegetation[i]);
			modelMat = glm::scale(modelMat, glm::vec3(2, 2, 2));
			grassShader->SetUniformMatrix4fv("model", modelMat);
			grassShader->SetUniformMatrix4fv("view", viewMat);
			grassShader->SetUniformMatrix4fv("projection", projMat);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader->Use();
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default

		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
		// clear all relevant buffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->Use();
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);	// use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);

		

		// Clean up, prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();//执行事件

	}
#pragma endregion

	#pragma region Exit Program
	// Exit Program
	glfwTerminate();
	return 0;
#pragma endregion

}

