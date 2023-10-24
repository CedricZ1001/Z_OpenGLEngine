#define GLEW_STATIC
#include<iostream>
#include <GL/glew.h>
#include<GLFW/glfw3.h>


/*透视投影
{
f/aspect,	0,		0,			0,
	0,		f,		0,			0,
	0,		0,(f+n)/(n-f),	(2*f*n)/(n-f),
	0，		0,		-1,			0
}
*/


//float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.0f, 0.5f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//	 0.9f,  0.5f,  0.0f
//};
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 //0.5f, -0.5f, 0.0f,
	 //0.0f, 0.5f, 0.0f,
	 0.9f,  0.5f,  0.0f
};
//0,1,2    2,1,3
unsigned int indices[] = {
	0,1,2,
	2,1,3
};

const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 6) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"vertexColor = vec4(1.0,0.3,0.4,0.6);\n"
"}\n";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"
"void main(){\n"
"FragColor = ourColor;}\n";



void processInput(GLFWwindow* window ) { //输入检测
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
} 

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//3.3开始使用可编程渲染管线
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//早期固定流水线，现在可编程化流水线一般都使用GLFW_OPENGL_CORE_PROFILE，另一个配置GLFW_OPENGL_COMPAT_PROFILE可以使用过时的特性和固定流水线
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // on Mac OS X you need to add

	GLFWwindow* window = glfwCreateWindow(800,600,"MY OpenGL Game",NULL,NULL);
	// Open GLFW window
	if (window == NULL)
	{
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

	glViewport(0, 0, 800, 600); //设置视口(Viewport)的大小 及定义屏幕上绘制图形的位置和大小
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

	//挖取VBO中的数据 做解释
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	//init shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//获取事件 找到ourcolor的地址
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	

	while (!glfwWindowShouldClose(window)) {
		
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);//The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT.
		
		timeValue = glfwGetTime();
		greenValue = (sin(timeValue) / 2) + 0.5f;
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();//执行事件

		
	}
	glfwTerminate();
	return 0;
}

