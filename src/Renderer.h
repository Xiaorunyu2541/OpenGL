#pragma once
#include <GLEW\glew.h>
#include <print>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__));


void GLClearError();

bool GLLogCall(const char* func_name, const char* filename, int line);

class Renderer 
{
private:

public:
    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh) const;
};