#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include"Shader.h"
#include"Loadimg.h"
#include"Camera.h"
#include"Material.h"
#include"LightDirectional.h"
#include"LightPoint.h"
#include"LightSpot.h"

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
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

#pragma endregion

#pragma region Light Declare

//LightDirectional* light = new LightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), 0, 0));

//LightPoint* light = new LightPoint(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), 0, 0));

LightSpot* light = new LightSpot(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0, 0));

#pragma endregion

#pragma region Camera Declare
//init camera
//Camera* mycamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
Camera* mycamera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(5.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Input Declare
float lastX;
float lastY;
bool isFirstMouse = true;

void ProcessInput(GLFWwindow* window ) { //输入检测
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	mycamera->speedX = 0;
	mycamera->speedY = 0;
	mycamera->speedZ = 0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mycamera->speedZ = 0.1;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mycamera->speedZ = -0.1;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mycamera->speedX = -0.1;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mycamera->speedX = 0.1;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		mycamera->speedY = 0.1;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		mycamera->speedY = -0.1;
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (isFirstMouse) {
		lastX = xPos;
		lastY = yPos;
		isFirstMouse = false;
	}
	double deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	mycamera->ProcessMouseMovement(deltaX, deltaY);
	lastX = xPos;
	lastY = yPos;

}
#pragma endregion



int main() {

	#pragma region Open Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);//3.3开始使用可编程渲染管线
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//早期固定流水线，现在可编程化流水线一般都使用GLFW_OPENGL_CORE_PROFILE，另一个配置GLFW_OPENGL_COMPAT_PROFILE可以使用过时的特性和固定流水线
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // on Mac OS X you need to add

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "MY OpenGL Game", NULL, NULL);
	// Open GLFW window
	if (window == NULL) {
		printf("failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	//Init GLEW
	glewExperimental = true; //实验性模式
	if (glewInit() != GLEW_OK) {
		printf("init glew failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 1920, 1080); //设置视口(Viewport)的大小 及定义屏幕上绘制图形的位置和大小

	glEnable(GL_DEPTH_TEST);
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_BLEND);//混合模式
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#pragma endregion

	#pragma region Load IMG
	//load img
	//Loadimg* awesome = new Loadimg("awesomeface.png",GL_RGBA, GL_RGBA);
	Loadimg* container = new Loadimg("assets/Material/Texture/container.png", GL_RGBA, GL_RGBA);
	Loadimg* container_specular = new Loadimg("assets/Material/Texture/container_specular.png", GL_RGBA, GL_RGBA);

#pragma endregion

	#pragma region Init VBO and VAO
	//声明VBO 存储模型数据
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//声明VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//挖取VBO中的顶点坐标数据 放入VAO中
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
#pragma endregion

	#pragma region Init Shader
	//init shader
	Shader* myshader = new Shader("assets/Material/Shader/vertexSource.vert", "assets/Material/Shader/fragmentSource.frag");
#pragma endregion

	#pragma region Init Material
	Material* myMaterial = new Material(myshader,
		glm::vec3(0.7f, 0.5f, 0.3f),
		glm::vec3(0.3f, 0.2f, 0.2f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		64);
	Material* containerMaterial = new Material(myshader,
		container->TexBuffer,
		glm::vec3(1.0f, 1.0f, 1.0f),
		container_specular->TexBuffer,
		64);

#pragma endregion

	#pragma region Perpare MVP
	//model mat
	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	projMat = glm::perspective( glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

#pragma endregion

	#pragma region Render Loop
	while (!glfwWindowShouldClose(window)) {
		// ProcessInput
		ProcessInput(window);

		// Clear Screen
		//glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.
		
		for (int i = 0; i < 10; i++)
		{
			// Set ModelMatrix
			modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, cubePositions[i]);
			//modelMat = glm::rotate(modelMat, glm::radians(i*45.0f), glm::vec3(1, 0, 0));
			//modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			// Set ViewMatrix
			viewMat = mycamera->GetViewMatrix();

			// Set Material -> Shader Program
			myshader->Use();	
			
			// Set Material -> Textures
			//glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, awesome->TexBuffer);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, containerMaterial->diffuseTexture);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, containerMaterial->specularTexture);

			// Set Material -> Uniform
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			//glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(myshader->ID, "leatherTexture"), 1);
			glUniform3f(glGetUniformLocation(myshader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myshader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);

			glUniform3f(glGetUniformLocation(myshader->ID, "lightPos"), light->position.x, light->position.y, light->position.z);
			glUniform3f(glGetUniformLocation(myshader->ID, "lightDirUniform"), light->direction.x, light->direction.y, light->direction.z);
			glUniform3f(glGetUniformLocation(myshader->ID, "lightColor"), light->color.r, light->color.g, light->color.b);
			
			//glUniform1f(glGetUniformLocation(myshader->ID, "lightPoint.constant"), light->constant);
			//glUniform1f(glGetUniformLocation(myshader->ID, "lightPoint.linear"), light->linear);
			//glUniform1f(glGetUniformLocation(myshader->ID, "lightPoint.quadratic"), light->quadratic);
			glUniform1f(glGetUniformLocation(myshader->ID, "lightSpot.cosPhy"), light->cosPhy);

			myMaterial->shader->SetUniform3f("cameraPos", mycamera->position);
			myMaterial->shader->SetUniform3f("material.ambient", containerMaterial->ambient);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", containerMaterial->shininess);

			// Set Model
			glBindVertexArray(VAO);

			// DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// Clean up, prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();//执行事件
		mycamera->UpdateCameraPos();
	}
#pragma endregion

	#pragma region Exit Program
	// Exit Program
	glfwTerminate();
	return 0;
#pragma endregion

}

