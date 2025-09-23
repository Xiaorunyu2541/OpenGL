#pragma once

#include <GLEW\glew.h>
#include <vector>
#include <stdint.h>
#include "Renderer.h"

struct VertexBufferElement 
{
	uint32_t type;
	uint32_t count;
	uint8_t normalized;

	static uint32_t GetTypeSize(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT:         return 4;
		case GL_UNSIGNED_INT:  return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
			return 0;
	}
};

class VBLayout 
{
private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
public:
	VBLayout()
		: m_Stride(0) {}
	~VBLayout() = default;

	template<typename T>
	void Push(uint32_t count)
	{
		static_assert(false, "Not handling this type yet");
		__debugbreak;
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
	}

	template<>
	void Push<uint32_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
	}

	template<>
	void Push<uint8_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline uint32_t GetStride() const { return m_Stride; }
};