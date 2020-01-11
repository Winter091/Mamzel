#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elems)
	:elements(elems)
{
	this->stride = 0;
	for (auto& elem : this->elements)
	{
		this->stride += elem.size;
	}
}

VertexBufferLayout::~VertexBufferLayout()
{
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
	return this->elements;
}
