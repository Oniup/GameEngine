#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include "Kryos/Renderer/RHI/GraphicsContext.h"
#include "Kryos/Renderer/RHI/WindowBase.h"
#include <string_view>

namespace Kryos
{

	class RendererContext : public ApplicationModule
	{
	public:
		RendererContext(const std::string_view windowTitle, RHI::WindowOptionFlags windowFlags = RHI::WindowOptionFlags());
		~RendererContext() override;

		RHI::GraphicsContext& GetGraphicsContext() { return m_GraphicsContext; }
		RHI::WindowBase& GetMainWindow() { return m_Window; }
		const RHI::WindowBase& GetMainWindow() const { return m_Window; }
		const RHI::GraphicsContext& GetGraphicsContext() const { return m_GraphicsContext; }

	private:
		RHI::GraphicsContext m_GraphicsContext;
		RHI::Window m_Window;
	};

}
