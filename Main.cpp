#include <iostream>
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Libraries/utilities/shader.h"



// main function what can i say
int main() {

	// initialization code for GLFW (library for OpenGL graphics and window)
	glfwInit();

	// set the version of OpenGL to be used by glfw
	specifyVersion();

	// create a GLFWwindow object named window passing in the size in pixels and the name
	GLFWwindow* window = glfwCreateWindow(800, 500, "Isometric Revisit", NULL, NULL);

	// incase the window is not created, print to the console and terminate the program
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// tell glfw what window we're talking about (i guess)
	glfwMakeContextCurrent(window);

	// load the glad library that will be used for actual graphics
	gladLoadGL();

	// create like a virtual window
	glViewport(0, 0, 800, 500);

	GLuint shaderProgram = createShaderProgram();

	//create the x offset variable and the variable responsible for changing it
	double x_pos = 0;
	bool increasing = true;

	// specify the x, y and z coordinates of the vertices of the triangle (goes from -1 to 1 in bot x and y)
	GLfloat vertices[] = {
		-0.4f + x_pos, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.4f + x_pos, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f + x_pos, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	// "reference containers" VAO for vertex array state, VBO for vertex buffer state
	GLuint VAO, VBO;

	std::tie(VAO, VBO) = setupVertexArray(vertices);


	// while loop so the window doesn't immediately close (stays open till 'X' is clicked)
	while (!glfwWindowShouldClose(window)) {

		// set the background color to navy blue
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// specify the x, y and z coordinates of the vertices of the triangle (goes from -1 to 1 in bot x and y)
		GLfloat vertices[] = {
			-0.4f + x_pos, -0.5f * float(sqrt(3)) / 3, 0.0f,
			0.4f + x_pos, -0.5f * float(sqrt(3)) / 3, 0.0f,
			0.0f + x_pos, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (increasing) {
			x_pos += 0.01;
			if (x_pos > 0.3) {
				increasing = false;
			}
		} else {
			x_pos -= 0.01;
			if (x_pos < -0.3) {
				increasing = true;
			}
		}

		// using the shader program, draw the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// bring the next frame into frame essentially
		glfwSwapBuffers(window);

		// still 'be alert' for 'X' clicking
		glfwPollEvents();
	}

	// Delete all the objects we created and don't need anymore
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// close the window and terminate the library using
	glfwDestroyWindow(window);
	glfwTerminate();


	// classic C++
	return 0;
}