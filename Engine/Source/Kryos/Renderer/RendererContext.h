#pragma once

#include "Kryos/Core/ApplicationInfo.h"
#include "Kryos/Core/ApplicationModule.h"
#include "Kryos/Renderer/ImGuiContext.h"
#include "Kryos/Renderer/RHI/Window.h"
#include "Kryos/Renderer/RHI/Shader.h"
#include "Kryos/Renderer/RHI/VertexBuffer.h"
#include <string_view>

namespace Kryos
{

	class RendererContext : public ApplicationModule
	{
	public:
		RendererContext(const ApplicationInfo& info, WindowOptionFlags windowFlags = WindowOptionFlags(), bool enableContextValidationLayers = true);
		~RendererContext() override;

		inline Window& GetMainWindow() { return m_Window; }
		inline const Window& GetMainWindow() const { return m_Window; }
		inline const std::string& GetGlslVersion() const { return m_GlslVersion; }
		inline void SetImGuiContext(ImGuiContext* context) { m_ImGui = context; }

		void DrawFrame();

	private:
		Window m_Window;
		ImGuiContext* m_ImGui = nullptr;
		Shader m_Shader;
		VertexBuffer m_Buffer;
		// uint32_t m_Buffers[3];
		std::string m_GlslVersion;
	};

}
