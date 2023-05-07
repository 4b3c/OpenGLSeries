#include "shader.h"
#include <cstddef>

#include <utility>

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

void specifyVersion() {
	// set the version of OpenGL to be used by glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLuint createShaderProgram() {

	// creates the vertex shader (using code at the top as source) this also compiles it into machine code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// creates the fragment shader (also using code at the top) this also compiles it into machine code
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// creates the shader program and attaches both the vertex and fragment shaders to it
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// after adding both shaders to the shader program we can delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

std::pair<GLuint, GLuint> setupVertexArray(float* vertices) {
	// "reference containers" VAO for vertex array state, VBO for vertex buffer state
	GLuint VAO, VBO;

	// generate and bind the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// generate and bind the VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// copy all the vertices data to the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// tell openGL how to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// bind them to zero so we don't accidentally modify them apparantly
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// return VAO and VBO
	return std::make_pair(VAO, VBO);
}