#ifndef BUFFERS_H
#define BUFFERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tuple>

using namespace std;

tuple<GLuint, GLuint> setupVertexArray(float* vertices, int verSize);


#endif