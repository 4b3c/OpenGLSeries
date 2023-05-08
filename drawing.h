#ifndef DRAWING_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "buffers.h"

using namespace std;

void draw_tile(int x, int y, int width, int* windowSize, GLuint shaderProgram, GLFWwindow* window);

#endif // !DRAWING_H
