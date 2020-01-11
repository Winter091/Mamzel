#include "VertexArray.h"
#include "../../util/ErrorHandling.h"

#include <iostream>


VertexArray::VertexArray()
{
	HANDLE_ERROR(glGenVertexArrays(1, &this->m_VertexArrayID));
	Bind();
	m_VertexCount = -1;
	m_IndexCount = -1;
}

VertexArray::VertexArray(std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout)
{
	HANDLE_ERROR(glGenVertexArrays(1, &this->m_VertexArrayID));

	Bind();
	vb->Bind();

	m_VertexCount = vb->GetCount() / (layout.GetStride() / sizeof(float));
	m_IndexCount = -1;

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements[i];

		HANDLE_ERROR(glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (void*)offset));
		HANDLE_ERROR(glEnableVertexAttribArray(i));

		offset += e.count * VertexBufferElement::GetTypeSize(e.type);
	}

	Unbind();
}

VertexArray::VertexArray(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib, const VertexBufferLayout& layout)
{
	HANDLE_ERROR(glGenVertexArrays(1, &this->m_VertexArrayID));

	Bind();
	vb->Bind();
	ib->Bind();

	m_VertexCount = vb->GetCount() / (layout.GetStride() / sizeof(float));
	m_IndexCount = ib->GetCount();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements[i];

		HANDLE_ERROR(glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (void*)offset));
		HANDLE_ERROR(glEnableVertexAttribArray(i));

		offset += e.count * VertexBufferElement::GetTypeSize(e.type);
	}

	Unbind();
}

VertexArray::~VertexArray()
{
	HANDLE_ERROR(glDeleteVertexArrays(1, &this->m_VertexArrayID));
}

std::shared_ptr<VertexArray> VertexArray::Create(std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout)
{
	return std::make_shared<VertexArray>(vb, layout);
}

std::shared_ptr<VertexArray> VertexArray::Create(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<IndexBuffer>& ib, const VertexBufferLayout& layout)
{
	return std::make_shared<VertexArray>(vb, ib, layout);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	m_VertexCount = vb.GetCount() / (layout.GetStride() / sizeof(float));

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		HANDLE_ERROR(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset));
		HANDLE_ERROR(glEnableVertexAttribArray(i));

		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}
	Unbind();
}

void VertexArray::AddIndexBuffer(const IndexBuffer& ib)
{
	Bind();
	ib.Bind();
	m_IndexCount = ib.GetCount();
	Unbind();
}

void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb->Bind();

	m_VertexCount = vb->GetCount() / (layout.GetStride() / sizeof(float));

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		HANDLE_ERROR(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset));
		HANDLE_ERROR(glEnableVertexAttribArray(i));

		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}

	Unbind();
}

void VertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer>& ib)
{
	Bind();
	ib->Bind();
	m_IndexCount = ib->GetCount();
	Unbind();
}

void VertexArray::Bind() const
{
	HANDLE_ERROR(glBindVertexArray(this->m_VertexArrayID));
}

void VertexArray::Unbind() const
{
	HANDLE_ERROR(glBindVertexArray(0));
}