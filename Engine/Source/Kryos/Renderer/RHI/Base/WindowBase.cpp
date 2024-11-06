#include "Kryos/Renderer/RHI/Base/WindowBase.h"
#include <GLFW/glfw3.h>

namespace Kryos::RHI
{

	WindowBase::WindowBase(GraphicsContext* context, WindowOptionFlags flags)
		: m_Window(nullptr), m_Flags(flags), m_Context(context)
	{
	}

	WindowBase::~WindowBase()
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
			m_Context = nullptr;
			m_Flags = WindowOptionFlag_Invalid;
		}
	}

	bool WindowBase::ValidateFlags(WindowOptionFlags flags)
	{
		int modeCount = 0;
		if (flags & WindowOptionFlag_FullScreenMode) modeCount++;
		if (flags & WindowOptionFlag_BorderlessMode) modeCount++;
		if (flags & WindowOptionFlag_WindowedMode) modeCount++;
		return modeCount == 1;
	}

	glm::ivec2 WindowBase::GetSize()
	{
		glm::ivec2 size;
		glfwGetWindowSize(m_Window, &size.x, &size.y);
		return size;
	}

	glm::ivec2 WindowBase::GetFrameSize()
	{
		glm::ivec2 size;
		glfwGetFramebufferSize(m_Window, &size.x, &size.y);
		return size;
	}

	glm::ivec2 WindowBase::GetPosition()
	{
		glm::ivec2 position;
		glfwGetWindowPos(m_Window, &position.x, &position.y);
		return position;
	}

	void WindowBase::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void WindowBase::MakeCurrentContext()
	{
		glfwMakeContextCurrent(m_Window);
	}

	bool WindowBase::IsClosing() const
	{
		return glfwWindowShouldClose(m_Window);
	}

}