#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

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
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		


		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));




		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2);
		layout.Push(GL_FLOAT, 2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.7f, 0.5f, 0.0f, 1.0f);

		Texture texture("res/textures/grass1.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();


		Renderer renderer;


		float red = 0.0f;
		float increment = 0.03f;

		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			if (red > 1.0f || red < 0.0f)
				increment = -increment;

			red += increment;

			shader.Bind();
			shader.SetUniform4f("u_Color", red , 0.5f, 0.0f, 1.0f);
			
			renderer.Draw(va, ib, shader);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}