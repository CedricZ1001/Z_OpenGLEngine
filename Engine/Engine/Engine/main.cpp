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

//model data
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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


//init camera
//Camera* mycamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
Camera* mycamera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(5.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));


float lastX;
float lastY;
bool isFirstMouse = true;

void processInput(GLFWwindow* window ) { //输入检测
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (isFirstMouse) {
		lastX = xPos;
		lastY = yPos;
		isFirstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	mycamera->ProcessMouseMovement(deltaX, deltaY);
	lastX = xPos;
	lastY = yPos;
	
}

int main() {

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(8);

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//init shader
	Shader* myshader = new Shader("vertexSource.txt", "fragmentSource.txt");
	
	//load img
	Loadimg* awesome = new Loadimg("awesomeface.png");
	Loadimg* leather = new Loadimg("leather.png");

	//model mat
	glm::mat4 modelMat;
	glm::mat4 trans;
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat = glm::rotate(trans, glm::radians(-45.0f), glm::vec3(1.0f, 0, 0));
	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	glm::mat4 projMat;
	projMat = glm::perspective( glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	float x=1;
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		x+=0.1;
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.
		glBindVertexArray(VAO);
		
		viewMat = mycamera->GetViewMatrix();

		for (int i = 0; i < 10; i++)
		{
			myshader->Use();	
			glm::mat4 Mat;
			Mat = glm::translate(Mat, cubePositions[i]);
			Mat = glm::rotate(Mat, glm::radians(x), glm::vec3(1, 0, 0));
			//MVP
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(Mat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(myshader->ID, "leatherTexture"), 1);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, awesome->TexBuffer);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, leather->TexBuffer);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();//执行事件

	}

	glfwTerminate();
	return 0;
}

