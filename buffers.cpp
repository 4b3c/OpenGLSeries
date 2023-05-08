#include "buffers.h"
#include <iostream>

using namespace std;

tuple<GLuint, GLuint> setupVertexArray(GLfloat* vertices, int verSize) {
	// "reference containers" VAO for vertex array state, VBO for vertex buffer state
	GLuint VAO, VBO;

	// generate and bind the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// generate and bind the VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// copy all the vertices data to the buffer
	glBufferData(GL_ARRAY_BUFFER, verSize, vertices, GL_STATIC_DRAW);

	// tell openGL how to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// bind them to zero so we don't accidentally modify them apparantly
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// return VAO, VBO, and EBO
	return make_tuple(VAO, VBO);
}