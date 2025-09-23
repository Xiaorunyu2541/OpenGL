#include <GLEW/glew.h>
#include <sstream>
#include <fstream>
#include "Renderer.h"
#include "Shader.h"

Shader::Shader(const std::string& filepath)
	:m_Filepath(filepath), m_RendererID(0)
{
    Sources source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

bool Shader::CompileShader()
{
    return 0;
}

Sources Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#declare") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& src)
{
    uint32_t id = glCreateShader(type);
    const char* source = src.c_str();
    GLCall(glShaderSource(id, 1, &source, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* msg = (char*)alloca(sizeof(char) * length);
        GLCall(glGetShaderInfoLog(id, length, &length, msg));
        std::println("Failed to compile shader! Info: {}", msg);
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

 uint32_t Shader::CreateShader(const std::string vtx_shader, const std::string frag_shader)
{
    GLCall(uint32_t program = glCreateProgram());
    uint32_t vtx_compiled = CompileShader(GL_VERTEX_SHADER, vtx_shader);
    uint32_t frag_compiled = CompileShader(GL_FRAGMENT_SHADER, frag_shader);

    GLCall(glAttachShader(program, vtx_compiled));
    GLCall(glAttachShader(program, frag_compiled));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vtx_compiled));
    GLCall(glDeleteShader(frag_compiled));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const 
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetLocation(name), v1, v2, v3, v4));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetLocation(const std::string& name)
{
    if (m_ULCache.find(name) != m_ULCache.end()) //while using std::unordered_map if you parse in find() a invalid key it returns end()
        return m_ULCache[name];

    int location = 0;
    GLCall(location = glGetUniformLocation(m_RendererID, name.c_str()));

    if (location == -1)
        std::println("error invalid uniform");

        m_ULCache[name] = location;
    return location;
}