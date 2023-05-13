#pragma once

#include <vector>

#include "Renderer.h"

using namespace std;

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}

	VertexBufferElement(unsigned int c, unsigned int t, bool n) :
		type(c), count(t), normalized(n)
	{

	}
};


class VertexBufferLayout {
private:
	vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	void Push(unsigned int type, unsigned int count)
	{
		m_Elements.push_back({ type, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(type);
	}


	inline const vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};