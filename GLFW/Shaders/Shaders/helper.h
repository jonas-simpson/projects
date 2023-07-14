#ifndef HELPER_H
#define HELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* initOpenGL();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int createBO(const unsigned int id, GLenum bufferType, const float vertices[]);
unsigned int createBO(const unsigned int id, GLenum bufferType, const unsigned int indices[]);
unsigned int createShader(const GLenum shaderType, const char** shaderSource);
unsigned int createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader);
bool shaderCompileSuccess(const unsigned int shader);
bool shaderProgramLinkerSuccess(const unsigned int shaderProgram);

#endif
