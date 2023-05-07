#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utility>

GLuint createShaderProgram();
void specifyVersion();
std::pair<GLuint, GLuint> setupVertexArray(float* vertices);

#endif
