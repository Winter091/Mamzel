#include "VertexBuffer.h"
#include "../util/ErrorHandling.h"

#include "GL/glew.h"

VertexBuffer::VertexBuffer()
	:m_BufferID(-1), m_ElementCount(-1)
{
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	HANDLE_ERROR(glGenBuffers(1, &this->m_BufferID));
	this->Bind();
	HANDLE_ERROR(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	m_ElementCount = size / sizeof(float);
}

VertexBuffer::~VertexBuffer()
{
	HANDLE_ERROR(glDeleteBuffers(1, &this->m_BufferID));
}

void VertexBuffer::Bind() const
{
	HANDLE_ERROR(glBindBuffer(GL_ARRAY_BUFFER, this->m_BufferID));
}

void VertexBuffer::UnBind() const
{
	HANDLE_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
