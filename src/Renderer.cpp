#include "Renderer.h"

#include <iostream>

using namespace std;

void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		cout << "[OpenGL Error] (" << error << ") on line: " << line << " -> '" << function << "'\nIn file: " << file << endl;
		return false;
	}
	return true;
}