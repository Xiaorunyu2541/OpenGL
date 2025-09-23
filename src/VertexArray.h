#pragma once

#include "VertexBuffer.h"

class VBLayout;

class VertexArray
{
private:
	uint32_t m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& buffer, const VBLayout& layout);
};