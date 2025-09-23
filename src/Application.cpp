#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <print>
#include <format>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(960, 540, "Hello World!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::println("Init Failed");
    }
    else
    {
        std::println("Init Succeed! Version: {}", (char*)glGetString(GL_VERSION));
    }
    { //Context Scope
    float pos[] =
    {
       -50.0f, -50.0f, 0.0f, 0.0f, //0
        50.0f, -50.0f, 1.0f, 0.0f, //1
        50.0f,  50.0f, 1.0f, 1.0f, //2
       -50.0f,  50.0f, 0.0f, 1.0f  //3
    };

    uint32_t indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    VertexArray va;
    VertexBuffer vb(pos, 4 * 4 * sizeof(float));
    VBLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f,-1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Shader sh("res/shaders/Shaders.shader");
    sh.Bind();

    Texture tx("res/textures/target.png");
    tx.Bind();

    sh.SetUniform1i("u_Texture", 0);

    va.Unbind();
    sh.Unbind();
    vb.Unbind();
    ib.Unbind();

    float r = 0.0f;
    float increment = 0.1f;

    Renderer rdr;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    while (!glfwWindowShouldClose(window))
    {
        rdr.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 MVP = proj * view * model;
            sh.Bind();
            sh.SetUniformMat4f("u_MVP", MVP);

            rdr.Draw(va, ib, sh);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 MVP = proj * view * model;
            sh.Bind();
            sh.SetUniformMat4f("u_MVP", MVP);

            rdr.Draw(va, ib, sh);
        }

        if (r > 1.0f)
            increment = -0.02f;
        else if (r < 0.0f)
            increment =  0.02f;

        r += increment;
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f); 
            ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    } //begins at float[] pos
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}