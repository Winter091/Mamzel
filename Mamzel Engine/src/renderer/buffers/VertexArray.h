#pragma once

#include <memory>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
private:
	unsigned int m_VertexArrayID;
	int m_VertexCount;
	int m_IndexCount;

public:
	VertexArray();
	VertexArray(std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout);
	VertexArray(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib, const VertexBufferLayout& layout);
	~VertexArray();

	static std::shared_ptr<VertexArray> Create(std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout);
	static std::shared_ptr<VertexArray> Create(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib, const VertexBufferLayout& layout);

	void AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(const IndexBuffer& ib);

	void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout);
	void AddIndexBuffer(std::shared_ptr<IndexBuffer>& ib);

	inline int GetVertexCount() const { return m_VertexCount; }
	inline int GetIndexCount() const { return m_IndexCount; }

	void Bind() const;
	void Unbind() const;
};
