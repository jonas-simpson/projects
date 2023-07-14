#include "helper.h"
#include <iostream>

GLFWwindow* initOpenGL()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int createBO(const unsigned int id, GLenum bufferType, const float vertices[])
{
	//Create vertex buffer object and assign to buffer ID
	unsigned int VBO;
	glGenBuffers(id, &VBO);
	//Bind VBO to correct buffer type (vertex array buffer)
	glBindBuffer(bufferType, VBO);
	//Now, any buffer calls we make on GL_ARRAY_BUFFER will be used to configure VBO
	//Copy our vertex data into the buffer memory
	glBufferData(bufferType, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return VBO;
}
unsigned int createBO(const unsigned int id, GLenum bufferType, const unsigned int indices[])
{
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(bufferType, EBO);
	glBufferData(bufferType, sizeof(indices), indices, GL_STATIC_DRAW);

	return EBO;
}

unsigned int createShader(const GLenum shaderType, const char** shaderSource)
{
	//Create empty vertex shader object
	unsigned int shader;
	shader = glCreateShader(shaderType);
	//Attach shader source code to shader object and compile
	glShaderSource(shader, 1, shaderSource, NULL);
	glCompileShader(shader);

	return shader;
}

unsigned int createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader)
{
	//Create empty program object and store ID
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//Attach compiled shaders to program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link our two shaders together
	glLinkProgram(shaderProgram);


	return shaderProgram;
}

bool shaderCompileSuccess(const unsigned int shader)
{
	//Check for compile-time errors of our shader
	//Define an integer to indicate success
	int success;
	//Create storage container for potential error message
	char infolog[512];
	//Check if compilation is successful
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//If compilation failed...
	if (!success)
	{
		//Receive and store error message
		glGetShaderInfoLog(shader, 512, NULL, infolog);
		//Print error message
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
	}

	return success;
}

bool shaderProgramLinkerSuccess(const unsigned int shaderProgram)
{
	//Check for linker errors of our shader program
	//Define an integer to indicate success
	int success;
	//Create storage container for potential error message
	char infolog[512];
	//Check if compilation is successful
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//If compilation failed...
	if (!success)
	{
		//Receive and store error message
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		//Print error message
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
	}

	return success;
}
