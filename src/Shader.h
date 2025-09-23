#pragma once

#include <string>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>

struct Sources
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	uint32_t m_RendererID;
	std::string m_Filepath;
	std::unordered_map<std::string, int> m_ULCache;

	int GetLocation(const std::string& name);
	bool CompileShader();
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	Sources ParseShader(const std::string& filepath);
	uint32_t CreateShader(const std::string vtx_shader, const std::string frag_shader);
	uint32_t CompileShader(uint32_t type, const std::string& src);
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};