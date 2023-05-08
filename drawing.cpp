#include <iostream>
#include "drawing.h"

using namespace std;

GLuint VAO;
GLuint VBO;

void draw_tile(int x, int y, int width, int* windowSize, GLuint shaderProgram, GLFWwindow* window) {
	GLfloat vertices[] = {
		(((x - width) / windowSize[0]) * 2) - 1, ((y / windowSize[1]) * 2) - 1, 0.0f,
		((x / windowSize[0]) * 2) - 1, (((y - (width / 2)) / windowSize[1]) * 2) - 1, 0.0f,
		(((x + width) / windowSize[0]) * 2) - 1, ((y / windowSize[1]) * 2) - 1, 0.0f,
		((x / windowSize[0]) * 2) - 1, (((y + (width / 2)) / windowSize[1]) * 2) - 1, 0.0f
	};

	tuple<GLuint, GLuint> vaoTuple = setupVertexArray(vertices, sizeof(vertices));
	VAO = get<0>(vaoTuple);
	VBO = get<1>(vaoTuple);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glfwSwapBuffers(window);
	glfwPollEvents();

}
