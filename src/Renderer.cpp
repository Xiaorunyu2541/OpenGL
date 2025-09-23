#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func_name, const char* filename, int line)
{
    while (GLenum err_msg = glGetError())
    {
        std::println("GLErrorCode: [{0}], issue occured in function: {1} at file: {2}, line: {3}", err_msg, func_name, filename, line);
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh) const 
{
    sh.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}