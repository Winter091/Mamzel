#pragma once

#include <memory>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
private:
	unsigned int m_VertexArrayID;
	unsigned int m_IndexBufferCount;

public:
	VertexArray();
	VertexArray(std::unique_ptr<VertexBuffer>& vb, std::unique_ptr<IndexBuffer>& ib, const VertexBufferLayout& layout);
	~VertexArray();

	void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& ib);

	void AddVertexBuffer(std::unique_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer>& ib);

	inline unsigned int GetIndexCount() const { return m_IndexBufferCount; }

	void Bind() const;
	void Unbind() const;
};
