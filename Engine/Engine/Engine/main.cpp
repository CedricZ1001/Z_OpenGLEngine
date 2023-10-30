#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include"Shader.h"
#include "Loadimg.h"


/*透视投影
{
f/aspect,	0,		0,			0,
	0,		f,		0,			0,
	0,		0,(f+n)/(n-f),	(2*f*n)/(n-f),
	0，		0,		-1,			0
}*/

//float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.0f, 0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.9f,  0.5f,  0.0f
//};

//float vertices[] = {
//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
//	 //0.5f, -0.5f, 0.0f,
//	 //0.0f, 0.5f, 0.0f,
//	 0.9f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
//	 -0.9f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f
//};

float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

//0, 1, 2   2, 1, 3   2, 4, 0
//unsigned int indices[] = {
//	0, 1, 2,
//	2, 1, 3,
//	2, 4, 0
//};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

//const char* vertexShaderSource =
//"#version 330 core\n"
//"layout(location = 6) in vec3 aPos;\n"
//"layout(location = 7) in vec3 aColor;\n"
//"out vec4 vertexColor;\n"
//"void main(){\n"
//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0f);\n"
//"}\n";
//
//const char* fragmentShaderSource =
//"#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec4 vertexColor;\n"
////"uniform vec4 ourColor;\n"
//"void main(){\n"
//"FragColor = vertexColor;}\n";

void processInput(GLFWwindow* window ) { //输入检测
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//glm::vec4 vec(1.0f, 0.0f, 0.0f,1.0f);
	//std::cout << vec.x << vec.y << vec.z << std::endl;
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << vec.w;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//3.3开始使用可编程渲染管线
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//早期固定流水线，现在可编程化流水线一般都使用GLFW_OPENGL_CORE_PROFILE，另一个配置GLFW_OPENGL_COMPAT_PROFILE可以使用过时的特性和固定流水线
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // on Mac OS X you need to add

	GLFWwindow* window = glfwCreateWindow(1080, 960, "MY OpenGL Game", NULL, NULL);
	// Open GLFW window
	if (window == NULL) {
		printf("failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	//Init GLEW
	glewExperimental = true; //实验性模式
	if (glewInit() != GLEW_OK) {
		printf("init glew failed");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 1080, 960); //设置视口(Viewport)的大小 及定义屏幕上绘制图形的位置和大小

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
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);

	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(7);

	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(8);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//init shader
	Shader* myshader = new Shader("vertexSource.txt", "fragmentSource.txt");
	
	//load img
	Loadimg* awesome = new Loadimg("awesomeface.png");
	Loadimg* leather = new Loadimg("leather.png");

	//获取事件 找到ourcolor的地址
	/*float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");*/
	
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1.0f));
	//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));
	//bool isbigger = true;s

	while (!glfwWindowShouldClose(window)) {
		glm::mat4 trans;
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));
		processInput(window);
		//std::cout << trans[3].x << std::endl;
		/*if (isbigger == false) {
			trans = glm::scale(trans, glm::vec3(0.99f, 0.99f, 0.99f));
			isbigger = trans[0].x < 1.0f ? 1 : 0;
		}
		else {
			trans = glm::scale(trans, glm::vec3(1.01f, 1.01f, 1.01f));
			isbigger = trans[0].x > 2.0f ? 0 : 1;
		}*/
		//trans = glm::translate(trans, glm::vec3(0.01f, 0.0f, 0.0f));
		//trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0, 0, 1.0f));
		
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.
		
		//timeValue = glfwGetTime();
		//greenValue = (sin(timeValue) / 2) + 0.5f;

		glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(myshader->ID, "leatherTexture"), 1);
		//calculate our transform
		unsigned int transformLoc = glGetUniformLocation(myshader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		myshader->Use();
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, awesome->TexBuffer);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, leather->TexBuffer);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();//执行事件

	}

	glfwTerminate();
	return 0;
}

