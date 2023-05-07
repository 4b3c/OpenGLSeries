#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tuple>

using namespace std;

GLuint createShaderProgram();
void specifyVersion();
tuple<GLuint, GLuint, GLuint> setupVertexArray(float* vertices, int verSize, GLuint* indices, int indSize);

#endif
