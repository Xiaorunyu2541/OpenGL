#pragma once

#include "Renderer.h"

class Texture
{
private:
	uint32_t m_RendererID;
	std::string m_FilePath;
	uint8_t* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;
};