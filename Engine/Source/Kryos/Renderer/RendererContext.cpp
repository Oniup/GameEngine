#include "Kryos/Core/Log.h"
#include "Kryos/Renderer/RendererContext.h"
#include "Kryos/Core/Defines.h"
#include <glad/glad.h>
#include <iostream>

namespace Kryos
{

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 Uv;
	};

	RendererContext::RendererContext(const ApplicationInfo& info, WindowOptionFlags windowFlags, bool enableContextValidationLayers)
		: m_Window(info.Name, -1, -1, windowFlags), m_GlslVersion(fmt::format("#version {}{}0 core", m_Window.GetOpenGLVersion().x, m_Window.GetOpenGLVersion().y))
	{
		KY_INFO("Initialized Renderer Context Module");

		m_Shader = Shader({
			ShaderSource(GetGlslVersion(), "../Engine/Assets/Sprite.frag", ShaderType_Fragment),
			ShaderSource(GetGlslVersion(), "../Engine/Assets/Sprite.vert", ShaderType_Vertex),
		});

		std::vector<uint32_t> indices = {
		    0, 1, 3, // first triangle
		    1, 2, 3  // second triangle
		};

		std::vector<Vertex> vertices = {
			Vertex {glm::vec3(0.5f, 0.5f, 0.0f),	glm::vec2(1.0f, 1.0f) }, // top right
			Vertex {glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec2(1.0f, 0.0f) }, // bottom right
			Vertex {glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec2(0.0f, 0.0f) }, // bottom left
			Vertex {glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec2(0.0f, 1.0f) }, // top left
		};

		m_Buffer = VertexBuffer(sizeof(Vertex) / sizeof(float), true);
		m_Buffer.RegisterElement(3); // Position
		m_Buffer.RegisterElement(2); // Uv
		m_Buffer.SetVertices(vertices.data(), vertices.size());
		m_Buffer.SetIndices(indices.data(), indices.size());
	}

	RendererContext::~RendererContext()
	{
		KY_INFO("Destroyed Renderer Context Module");
	}

	void RendererContext::DrawFrame()
	{
		glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader.Bind();
		m_Shader.Uniform("u_ShapeColor", glm::vec3(1.0f, 0.5f, 0.2f));
		m_Buffer.SubmitDrawData();
		m_Shader.Unbind();

	 	if (m_ImGui)
	 		m_ImGui->Draw(*this);
	}

}