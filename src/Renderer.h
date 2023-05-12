#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))


void GLClearErrors();

bool GlLogCall(const char* function, const char* file, int line);