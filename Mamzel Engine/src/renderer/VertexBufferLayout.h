#pragma once

#include "GL/glew.h"

#include <vector>
#include <string>

struct VertexBufferElement
{
	std::string name;
	unsigned int type;
	unsigned int count;
	unsigned int size;
	bool normalized;

	static int GetTypeSize(int type)
	{
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_BYTE: return 1;
		default: return 0;
		}
	}

	VertexBufferElement(int type, int count, std::string name)
		:name(name), type(type), count(count), size(GetTypeSize(type)* count), normalized(false)
	{
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;

public:
	VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elems);
	~VertexBufferLayout();

	const std::vector<VertexBufferElement>& GetElements() const;
	int GetStride() const { return this->stride; }
};

