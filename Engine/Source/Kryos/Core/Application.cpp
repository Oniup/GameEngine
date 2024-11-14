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
		int initResult = glfwInit();
		KY_ASSERT(initResult, "Failed to initialize glfw");
		s_Instance = this;
	}

	Application::~Application()
	{
		for (auto it = m_Modules.rbegin(); it != m_Modules.rend(); it++)
			delete it->second;
		glfwTerminate();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glfwPollEvents();
			if (m_Renderer->GetMainWindow().IsClosing())
				m_Running = false;

			Time::UpdateDeltaTime();

			for (auto& [id, modules] : m_Modules)
				modules->OnUpdate();

			m_Renderer->DrawFrame();
			m_Renderer->GetMainWindow().SwapBuffers();
		}
	}

	void Application::SetupRequiredModules()
	{
		m_Renderer = PushModule<RendererContext>(m_Info);
	}

}