#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {

	// initialization code for GLFW (library for OpenGL graphics and window)
	glfwInit();

	// set the version of OpenGL to be used by glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	glViewport(0, 0, 800, 800);

	// set the 'virtual window' to a navy blue color (with alpha of 1)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bring the next frame into fram essentially
	glfwSwapBuffers(window);

	// while loop so the window doesn't immediately close (stays open till 'X' is clicked)
	while (!glfwWindowShouldClose(window)) {
		// still 'be alert' for 'X' clicking
		glfwPollEvents();
	}

	// close the window and terminate the library using
	glfwDestroyWindow(window);
	glfwTerminate();


	// classic C++
	return 0;
}