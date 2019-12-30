#pragma once


class VertexBuffer
{
private:
	unsigned int m_BufferID;
	int m_ElementCount;

public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	inline int GetCount() const { return m_ElementCount; }

	void Bind() const;
	void UnBind() const;

};