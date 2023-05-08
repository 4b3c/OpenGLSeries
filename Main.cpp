#include <iostream>
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Libraries/utilities/shader.h"
#include "buffers.h"
#include "drawing.h"

using namespace std;

// main function what can i say
int main() {

	// initialization code for GLFW (library for OpenGL graphics and window) and specify the version
	glfwInit();
	specifyVersion();

	// create a GLFWwindow object named window passing in the size in pixels and the name
	int windowSize[] = {800, 800};
	GLFWwindow* window = glfwCreateWindow(windowSize[0], windowSize[1], "Isometric Revisit", NULL, NULL);

	// incase the window is not created, print to the console and terminate the program
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// tell glfw what window we're talking about (i guess) and load the glad library that will be used for actual graphics
	glfwMakeContextCurrent(window);
	gladLoadGL();

	// create like a virtual window and shaderprogram
	glViewport(0, 0, windowSize[0], windowSize[1]);
	GLuint shaderProgram = createShaderProgram();

	//create the x offset variable and the variable responsible for changing it
	double x_pos = 0;
	bool increasing = true;

	cout << "Starting the loop..." << endl;

	// while loop so the window doesn't immediately close (stays open till 'X' is clicked)
	while (!glfwWindowShouldClose(window)) {

		// set the background color to navy blue
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (increasing) {x_pos += 0.01;
			if (x_pos > 0.3) {increasing = false;}
		} else {x_pos -= 0.01;
			if (x_pos < -0.3) {increasing = true;}
		}

		draw_tile(5, 5, 10, windowSize, shaderProgram, window);
	}

	glDeleteProgram(shaderProgram);

	// close the window and terminate the library using
	glfwDestroyWindow(window);
	glfwTerminate();

	// classic C++
	return 0;
}