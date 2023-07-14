#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
//#include <iostream>
#include "helper.h"
//#include "shaderSource.h"
#include "vertices.h"
#include "shader.h"

int main()
{
	GLFWwindow* window = initOpenGL();
	if (window == NULL)
		return -1;

	// Create our vertex data
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create vertex shader
	Shader ourShader("shader.vs", "shader.fs");
	/*
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	shaderCompileSuccess(vertexShader);

	//Create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	shaderCompileSuccess(fragmentShader);

	//Create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	shaderProgramLinkerSuccess(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	*/

	//Create vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	//RENDER TIME!!!
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//activate the shader
		//glUseProgram(shaderProgram);
		ourShader.use();

		//update uniform color
		float timeValue = glfwGetTime();
		float offset = sin(timeValue) / 2.0f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//ourShader.setFloat("ourColor", greenValue);
		ourShader.setFloat("xOffset", offset);

		//Draw the object!
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//Check and call all events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}