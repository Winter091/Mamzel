#include "IndexBuffer.h"
#include "../util/ErrorHandling.h"

#include "GL/glew.h"

#include <iostream>

IndexBuffer::IndexBuffer()
	:m_BufferID(-1), m_IndexCount(0)
{
}

IndexBuffer::IndexBuffer(const void* data, int size)
{
	HANDLE_ERROR(glGenBuffers(1, &this->m_BufferID));
	this->Bind();
	HANDLE_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	m_IndexCount = size / sizeof(unsigned int);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	HANDLE_ERROR(glDeleteBuffers(1, &this->m_BufferID));
}

void IndexBuffer::Bind() const
{
	HANDLE_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_BufferID));
}

void IndexBuffer::Unbind() const
{
	HANDLE_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
