#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// apparantly this is the vertex shader (takes in x, y, z it looks like)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// and this is the fragment shader source code, idek what that means
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main () {\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


// main function what can i say
int main() {

	// initialization code for GLFW (library for OpenGL graphics and window)
	glfwInit();

	// set the version of OpenGL to be used by glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// specify the x, y and z coordinates of the vertices of the triangle (goes from -1 to 1 in bot x and y)
	GLfloat vertices[] = {
		-0.4f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.4f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

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

	// creates the vertex shader (using code at the top as source) this also complis it into machine code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// creates the fragment shader (also using code at the top) this also complis it into machine code
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// creates the shader program (?) and attaches both the vertex and fragment shaders to it
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// after adding both shaders to the shader program we can delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// "reference containers" for the vertex array
	GLuint VAO, VBO;

	// tbh, no clue at all
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// bind them to zero so we don't accidentally modify them apparantly
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	// set the 'virtual window' to a navy blue color (with alpha of 1)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// while loop so the window doesn't immediately close (stays open till 'X' is clicked)
	while (!glfwWindowShouldClose(window)) {

		// set the background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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