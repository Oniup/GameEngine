#include "Kryos/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Kryos
{

	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationInfo&& info)
		: m_Info(std::move(info))
	{
		s_Instance = this;
	}

	Application::~Application()
	{
		for (auto it = m_Modules.rbegin(); it != m_Modules.rend(); it++)
			delete it->second;
	}

	void Application::Run()
	{
		while (!m_Renderer->GetMainWindow().IsClosing())
		{
		 	glClearColor(0.2f, 0.6f, 0.9f, 1.0f);
		 	glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();
			m_Renderer->GetMainWindow().SwapBuffers();
		}
	}

	void Application::SetupRequiredModules()
	{
		m_Renderer = PushModule<RendererContext>(m_Info.Name);
	}

}