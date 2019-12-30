#pragma once


class IndexBuffer
{
private:
	unsigned int m_BufferID;
	int m_IndexCount;

public:
	IndexBuffer();
	IndexBuffer(const void* data, int size);
	~IndexBuffer();

	inline int GetCount() const { return m_IndexCount; }

	void Bind() const;
	void Unbind() const;
};