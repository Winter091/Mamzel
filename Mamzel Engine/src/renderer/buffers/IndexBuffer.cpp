#include "IndexBuffer.h"
#include "../../util/ErrorHandling.h"

#include <iostream>

IndexBuffer::IndexBuffer()
	:m_BufferID(-1), m_IndexCount(-1)
{
}

IndexBuffer::IndexBuffer(const void* data, unsigned int size, int usage)
{
	HANDLE_ERROR(glGenBuffers(1, &this->m_BufferID));
	this->Bind();
	HANDLE_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
	m_IndexCount = size / sizeof(unsigned int);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	HANDLE_ERROR(glDeleteBuffers(1, &this->m_BufferID));
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const void* data, unsigned int size, int usage)
{
	return std::make_shared<IndexBuffer>(data, size, usage);
}

void IndexBuffer::Bind() const
{
	HANDLE_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_BufferID));
}

void IndexBuffer::Unbind() const
{
	HANDLE_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
