#include "TestTexture2D.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {

	TestTexture2D::TestTexture2D() 
		: m_translationA(400, 200, 0), m_translationB(200, 200, 0),
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
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

		m_Shader = std::make_unique<Shader>("res/shaders/Shaders.shader");

		m_VAO = std::make_unique<VertexArray>();

		VertexArray va;
		m_VBO = std::make_unique<VertexBuffer>(pos, 4 * 4 * sizeof(float));
		VBLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/target.png");

		m_Shader->SetUniform1i("u_Texture", 0);

	}

	TestTexture2D::~TestTexture2D()
	{
	
	}

	void TestTexture2D::OnUpdate(float DeltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		 

		Renderer rdr;

		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4 MVP = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", MVP);

			rdr.Draw(*m_VAO, *m_IBO, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4 MVP = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", MVP);

			rdr.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Begin("Texture Test");                          // Create a window called "Hello, world!" and append into it.

		ImGui::SliderFloat3("TranslationA", &m_translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("TranslationB", &m_translationB.x, 0.0f, 960.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}