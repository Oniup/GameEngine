#include "Kryos/Renderer/RHI/Base/GraphicsContextBase.h"
#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Log.h"
#include <GLFW/glfw3.h>

namespace Kryos::RHI
{

	static void GlfwErrorCallback(int error, const char* description)
	{
		KY_ERROR("GLFW Error {}: {}", error, description);
	}

	GraphicsContextBase::GraphicsContextBase()
	{
		glfwSetErrorCallback(GlfwErrorCallback);

		int result = glfwInit();
		KY_ASSERT(result, "Failed to initialize GLFW");
	}

	GraphicsContextBase::~GraphicsContextBase()
	{
		glfwTerminate();
	}

}
