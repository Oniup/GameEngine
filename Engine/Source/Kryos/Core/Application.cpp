#define GLFW_INCLUDE_NONE

#include "Kryos/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Kryos
{

	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification&& specification)
		: m_Secification(std::move(specification)), m_Running(true)
	{
		s_Instance = this;
	}

	Application::~Application()
	{
		for (auto entry : m_Modules)
			delete entry.second;
	}

	void Application::Run()
	{
		glfwInit();
		glfwWindowHint(GLFW_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_VERSION_MINOR, 6);
		const glm::ivec2 winSize = glm::ivec2(600, 600);
		GLFWwindow* window = glfwCreateWindow(winSize.x, winSize.y, "Test Window", nullptr, nullptr);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.7f, 0.5f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Application::SetupRequiredModules()
	{
		// ...
	}

}