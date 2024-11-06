#include "Kryos/Renderer/RHI/Base/GraphicsContextBase.h"
#include "Kryos/Core/Defines.h"
#include <GLFW/glfw3.h>

namespace Kryos::RHI
{

	GraphicsContextBase::GraphicsContextBase()
	{
		int result = glfwInit();
		KY_ASSERT(result, "Failed to initialize GLFW");
	}

	GraphicsContextBase::~GraphicsContextBase()
	{
		glfwTerminate();
	}

}
