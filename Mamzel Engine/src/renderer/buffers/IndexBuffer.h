#pragma once

#include <GL/glew.h>

#include <memory>

class IndexBuffer
{
private:
	unsigned int m_BufferID;
	int m_IndexCount;

public:
	IndexBuffer();
	IndexBuffer(const void* data, unsigned int size, int usage = GL_STATIC_DRAW);
	~IndexBuffer();

	static std::shared_ptr<IndexBuffer> Create(const void* data, unsigned int size, int usage = GL_STATIC_DRAW);

	inline int GetCount() const { return m_IndexCount; }

	void Bind() const;
	void Unbind() const;
};