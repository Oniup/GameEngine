#include "Kryos/Core/Log.h"
#include "Kryos/Renderer/RendererContext.h"

namespace Kryos
{

	RendererContext::RendererContext(const std::string_view windowTitle, RHI::WindowOptionFlags windowFlags /*= RHI::WindowOptionFlags()*/)
		: m_Graphics(), m_Window(&m_Graphics, windowTitle, -1, -1, windowFlags)
	{
		KY_INFO("Initializing Renderer Context Module");
	}

	RendererContext::~RendererContext()
	{
		KY_INFO("Destroying Renderer Context Module");
	}

	void RendererContext::DrawFrame()
	{
		if (m_ImGui)
			m_ImGui->Draw();
	}

}