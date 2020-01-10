#pragma once

#include <GL/glew.h>

#include <memory>

class VertexBuffer
{
private:
	unsigned int m_BufferID;
	int m_ElementCount;

public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size, int usage = GL_STATIC_DRAW);
	~VertexBuffer();

	static std::shared_ptr<VertexBuffer> Create(const void* data, unsigned int size, int usage = GL_STATIC_DRAW);

	inline int GetCount() const { return m_ElementCount; }

	void Bind() const;
	void UnBind() const;

};