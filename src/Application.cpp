#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

using namespace std;


struct shaderProgramSource {
	string vertexSource;
	string fragmentSource;
};


static shaderProgramSource parseShader(const string& filepath) {
	ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}


static unsigned int complileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));

		cout << "Failed to complile shader -> " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << endl;
		cout << message << endl;
		GLCall(glDeleteShader(id));

		return 0;
	}

	return id;
}


static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = complileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = complileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}













int main(void)
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(900, 500, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK)
		cout << "Error" << endl;

	cout << glGetString(GL_VERSION) << endl;

	{
		float positions[8] = {
			 0.0f,  0.2f,
			 0.4f,  0.0f,
			 0.0f, -0.2f,
			-0.4f,  0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};


		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));




		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		shaderProgramSource source = parseShader("res/shaders/basic.shader");
		unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
		GLCall(glUseProgram(shader));

		GLCall(int location = glGetUniformLocation(shader, "u_Color"));
		ASSERT(location != -1);
		GLCall(glUniform4f(location, 0.7f, 0.5f, 0.0f, 1.0f));






		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));





		float red = 0.0f;
		float increment = 0.03f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			if (red > 1.0f || red < 0.0f)
				increment = -increment;

			red += increment;



			GLCall(glUseProgram(shader));
			GLCall(glUniform4f(location, red, 0.5f, 0.0f, 1.0f));

			va.Bind();
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glDeleteProgram(shader);
	}

	glfwTerminate();
	return 0;
}