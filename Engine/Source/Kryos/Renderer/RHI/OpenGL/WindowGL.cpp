#include "Kryos/Renderer/RHI/OpenGL/WindowGL.h"
#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Kryos::RHI
{

	WindowGL::WindowGL(GraphicsContextGL* context, const std::string_view title, int width, int height, WindowOptionFlags flags)
		: WindowBase(context, flags)
	{
		KY_ASSERT(ValidateFlags(flags), 
			"Cannot have more than one window mode active. These options include: WindowOptionFlag_FullscreenMode, WindowOptionFlag_WindowedMode, and WindowOptionFlag_BorderlessMode");
		KY_ASSERT(title.data()[title.size()] == '\0', "Title must '\\0' termated string");

		glm::ivec2 version = context->GetMinimumAPIVersion();
		glfwWindowHint(GLFW_VERSION_MAJOR, version.x);
		glfwWindowHint(GLFW_VERSION_MINOR, version.y);

#ifdef KY_PLATFORM_MACOS
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
		context->InitializeOpenGL();

		KY_VERBOSE("Created OpenGL Window");
	}

	WindowGL::~WindowGL()
	{
		if (m_Window)
			KY_VERBOSE("Destroyed OpenGL Window");
	}

}
