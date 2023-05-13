#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

using namespace std;





int main(void)
{

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(900, 500, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

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

		Shader shader("res/shaders/basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.7f, 0.5f, 0.0f, 1.0f);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();





		float red = 0.0f;
		float increment = 0.03f;

		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			if (red > 1.0f || red < 0.0f)
				increment = -increment;

			red += increment;

			shader.Bind();
			shader.SetUniform4f("u_Color", red , 0.5f, 0.0f, 1.0f);
			va.Bind();
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}