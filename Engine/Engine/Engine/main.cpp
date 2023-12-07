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

float transparentVertices[] = {
	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

vector<glm::vec3> vegetation
{
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

int main(int argc, char* argv[]) {
	
	#pragma region Open Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);//3.3开始使用可编程渲染管线
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
#pragma endregion

	#pragma region Load IMG
	//load img
	//Loadimg* awesome = new Loadimg("awesomeface.png",GL_RGBA, GL_RGBA);
	//Loadimg* container = new Loadimg("assets/Material/Texture/container.png", GL_RGBA, GL_RGBA);
	//Loadimg* container_specular = new Loadimg("assets/Material/Texture/container_specular.png", GL_RGBA, GL_RGBA);

#pragma endregion
	
	#pragma region Init VBO and VAO
	//Mesh cube(vertices);
	std::filesystem::path exePath = argv[0];
	string path = exePath.parent_path().parent_path().parent_path().string() + "\\Engine\\assets\\Model\\nanosuit\\nanosuit.obj";
	/*cout << path << endl;*/
	Model model(path);
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
	Loadimg* transparentTex = new Loadimg("assets/Material/Texture/grass.png", GL_RGBA, GL_RGBA);
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	//glBindFramebuffer(GL_FRAMEBUFFER, FBO);
#pragma endregion

	#pragma region Init Shader
	//init shader
	//Shader* myshader = new Shader("assets/Material/Shader/SpotLight.vert", "assets/Material/Shader/SpotLight.frag");
	Shader* myshader = new Shader("assets/Material/Shader/Model_loading.vert", "assets/Material/Shader/Model_loading.frag");
	Shader* shaderSingleColor = new Shader("assets/Material/Shader/stencil_testing.vert", "assets/Material/Shader/stencil_testing.frag");
	Shader* grassShader = new Shader("assets/Material/Shader/vegetation.vert", "assets/Material/Shader/vegetation.frag");
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
		
		// Clear Screen
		//glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.

		// Shader Program
		myshader->Use();
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilMask(0xFF);

		// Set MVPMatrixs
		modelMat = glm::mat4(1.0f);
		modelMat = glm::translate(modelMat,glm::vec3(0, -1, 0));
		viewMat = mycamera->GetViewMatrix();
		projMat = glm::perspective(glm::radians(mycamera->zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		// Uniform
		myshader->SetUniformMatrix4fv("model", modelMat);
		myshader->SetUniformMatrix4fv("view", viewMat);
		myshader->SetUniformMatrix4fv("projection", projMat);

		myshader->SetUniform3fv("dirLight.direction", mycamera->forward);
		myshader->SetUniform3fv("dirLight.ambient", glm::vec3(0.2, 0.2, 0.2));
		myshader->SetUniform3fv("dirLight.diffuse", glm::vec3(0.8, 0.8, 0.8));
		myshader->SetUniform3fv("dirLight.specular", glm::vec3(1, 1, 1));

		myshader->SetUniform3fv("dirLight.viewPos", mycamera->position);
		// Set Model
		//glBindVertexArray(VAO);
		
		// DrawCall
		model.Draw(*myshader);
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
		grassShader->Use();
		glBindVertexArray(transparentVAO);
		glBindTexture(GL_TEXTURE_2D, transparentTex->TexBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, vegetation[i]);
			modelMat = glm::scale(modelMat, glm::vec3(2, 2, 2));
			grassShader->SetUniformMatrix4fv("model", modelMat);
			grassShader->SetUniformMatrix4fv("view", viewMat);
			grassShader->SetUniformMatrix4fv("projection", projMat);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	
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

