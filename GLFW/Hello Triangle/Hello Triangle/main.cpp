#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0;";

GLFWwindow* initOpenGL();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int createBO(const unsigned int id, GLenum bufferType, const float vertices[]);
unsigned int createBO(const unsigned int id, GLenum bufferType, const unsigned int indices[]);
unsigned int createShader(const GLenum shaderType, const char** shaderSource);
unsigned int createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader);
bool shaderCompileSuccess(const unsigned int shader);
bool shaderProgramLinkerSuccess(const unsigned int shaderProgram);

int main()
{
	GLFWwindow* window = initOpenGL();
	if (window == NULL)
		return -1;

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,	//top right
		 0.5f, -0.5f, 0.0f,	//bottom right
		-0.5f, -0.5f, 0.0f,	//bottom left
		-0.5f,  0.5f, 0.0f	//top left
	};
	unsigned int indices[] = {
		0, 1, 3,	//first triangle
		1, 2, 3		//second triangle
	};

	float verticesDoubleTri[] = {
		-0.375f,  0.5f, 0.0f,	//top left
		-0.75f,  -0.5f, 0.0f,	//bottom left
		 0.0f,   -0.5f, 0.0f,	//bottom middle
		 0.375f,  0.5f, 0.0f,	//top right
		 0.75f,  -0.5f, 0.0f	//bottom right
	};
	unsigned int indicesDoubleTri[] = {
		0, 1, 2,	//first triangle
		3, 4, 2		//second triangle
	};

	unsigned int VBO = createBO(1, GL_ARRAY_BUFFER, verticesDoubleTri);
	unsigned int EBO = createBO(1, GL_ELEMENT_ARRAY_BUFFER, indicesDoubleTri);

	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, &vertexShaderSource);
	shaderCompileSuccess(vertexShader);

	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, &fragmentShaderSource);
	shaderCompileSuccess(fragmentShader);

	unsigned int shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	shaderProgramLinkerSuccess(shaderProgram);

	//We now have a program object that we can activate
	glUseProgram(shaderProgram);
	//Every shader and rendering call after this command will now use this program object and its shaders

	//Delete shader objects after linking to program object. They are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//Bind Vertex Array Object
	glBindVertexArray(VAO);
	//Copy our vertex array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesDoubleTri), verticesDoubleTri, GL_STATIC_DRAW);
	//Copy our index array in an element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesDoubleTri), indicesDoubleTri, GL_STATIC_DRAW);
	//Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//RENDER TIME!!!
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw the object!
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//Check and call all events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;

}

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
