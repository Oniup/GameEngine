#include "Kryos/Core/Defines.h"
#include "Kryos/Renderer/RHI/OpenGL/GraphicsContextGL.h"
#include "Kryos/Core/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Kryos::RHI
{

	GraphicsContextGL::GraphicsContextGL(const glm::ivec2& glVersion)
		: GraphicsContextBase(), m_API(glVersion), m_GladInitialized(false)
	{
		KY_VERBOSE("Initialized OpenGL Graphics Context");
	}

	void GraphicsContextGL::InitializeOpenGL()
	{
		if (!m_GladInitialized)
		{
			int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			KY_ASSERT(result, "Failed to initialize GLAD, need to initialize glfw window before calling this function");
			m_GladInitialized = true;
			KY_VERBOSE("Initialized OpenGL Context through gladGLLoader");
		}
	}

	GraphicsContextGL::~GraphicsContextGL()
	{
		KY_VERBOSE("Destroying OpenGL Graphics Context");
	}

}

