#pragma once


class IndexBuffer
{
private:
	unsigned int m_BufferID;
	unsigned int m_IndexCount;

public:
	IndexBuffer();
	IndexBuffer(const void* data, int size);
	~IndexBuffer();

	inline unsigned int GetCount() const { return m_IndexCount; }

	void Bind() const;
	void Unbind() const;
};