#include "Kryos/Core/Application.h"
#include "Kryos/Core/Time.h"
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
			Time::UpdateDeltaTime();

		 	glClearColor(0.2f, 0.6f, 0.9f, 1.0f);
		 	glClear(GL_COLOR_BUFFER_BIT);

			for (auto& [id, modules] : m_Modules)
				modules->OnUpdate();

			glfwPollEvents();
			m_Renderer->DrawFrame();
			m_Renderer->GetMainWindow().SwapBuffers();
		}
	}

	void Application::SetupRequiredModules()
	{
		m_Renderer = PushModule<RendererContext>(m_Info.Name);
	}

}