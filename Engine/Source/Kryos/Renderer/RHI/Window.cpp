#include "Kryos/Renderer/RHI/Window.h"
#include "Kryos/Core/Log.h"
#include "Kryos/Core/Defines.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Kryos
{

	Window::Window(const std::string_view title, int width, int height, WindowOptionFlags flags)
		: m_Window(nullptr), m_Flags(flags)
	{
		KY_ASSERT(ValidateFlags(flags), 
			"Cannot have more than one window mode active. These options include: WindowOptionFlag_FullscreenMode, WindowOptionFlag_WindowedMode, and WindowOptionFlag_BorderlessMode");
		KY_ASSERT(title.data()[title.size()] == '\0', "Title must '\\0' termated string");

		glfwWindowHint(GLFW_VERSION_MAJOR, GetOpenGLVersion().x);
		glfwWindowHint(GLFW_VERSION_MINOR, GetOpenGLVersion().y);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (width < 0 || height < 0)
		{
			const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
			width = vidmode->width / 2;
			height = vidmode->height / 2;
		}

		if (flags & ~WindowOptionFlag_FullScreenMode)
			monitor = nullptr;

		m_Window = glfwCreateWindow(width, height, title.data(), monitor, nullptr);
		KY_ASSERT(m_Window, "Failed to create window");

		glfwMakeContextCurrent(m_Window);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KY_ASSERT(result, "Failed to initialize OpenGL");

		KY_VERBOSE("Created main window instance and initialized OpenGL context");
	}

	Window::~Window()
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
			m_Flags = WindowOptionFlag_Invalid;
		}
	}

	bool Window::ValidateFlags(WindowOptionFlags flags)
	{
		int modeCount = 0;
		if (flags & WindowOptionFlag_FullScreenMode) modeCount++;
		if (flags & WindowOptionFlag_BorderlessMode) modeCount++;
		if (flags & WindowOptionFlag_WindowedMode) modeCount++;
		return modeCount == 1;
	}

	glm::ivec2 Window::GetSize()
	{
		glm::ivec2 size;
		glfwGetWindowSize(m_Window, &size.x, &size.y);
		return size;
	}

	glm::ivec2 Window::GetFrameSize()
	{
		glm::ivec2 size;
		glfwGetFramebufferSize(m_Window, &size.x, &size.y);
		return size;
	}

	glm::ivec2 Window::GetPosition()
	{
		glm::ivec2 position;
		glfwGetWindowPos(m_Window, &position.x, &position.y);
		return position;
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::MakeCurrentContext()
	{
		glfwMakeContextCurrent(m_Window);
	}

	bool Window::IsClosing() const
	{
		return glfwWindowShouldClose(m_Window);
	}

}