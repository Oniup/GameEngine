#include "Kryos/Renderer/RendererContext.h"
#include "Kryos/Core/Log.h"

namespace Kryos
{

	RendererContext::RendererContext(const std::string_view windowTitle, RHI::WindowOptionFlags windowFlags /*= RHI::WindowOptionFlags()*/)
		: m_GraphicsContext(), m_Window(&m_GraphicsContext, windowTitle, -1, -1, windowFlags)
	{
		KY_INFO("Initializing Renderer Context Module");
	}

	RendererContext::~RendererContext()
	{
		KY_INFO("Destroying Renderer Context Module");
	}

}