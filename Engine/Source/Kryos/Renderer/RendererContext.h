#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include "Kryos/Renderer/RHI/GraphicsContext.h"
#include "Kryos/Renderer/ImGuiContext.h"
#include "Kryos/Renderer/RHI/WindowBase.h"
#include <string_view>

namespace Kryos
{

	class RendererContext : public ApplicationModule
	{
		friend ImGuiContext;

	public:
		RendererContext(const std::string_view windowTitle, RHI::WindowOptionFlags windowFlags = RHI::WindowOptionFlags());
		~RendererContext() override;

		inline RHI::GraphicsContext& GetGraphicsContext() { return m_Graphics; }
		inline RHI::WindowBase& GetMainWindow() { return m_Window; }
		inline const RHI::WindowBase& GetMainWindow() const { return m_Window; }
		inline const RHI::GraphicsContext& GetGraphicsContext() const { return m_Graphics; }

		void DrawFrame();

	private:
		RHI::GraphicsContext m_Graphics;
		RHI::Window m_Window;
		ImGuiContext* m_ImGui = nullptr;
	};

}
