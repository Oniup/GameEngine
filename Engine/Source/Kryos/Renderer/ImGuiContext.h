#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include "Kryos/Renderer/RHI/GraphicsContext.h"
#include <imgui/imgui.h>

namespace Kryos
{

	class ImGuiContext : public ApplicationModule
	{
	public:
		ImGuiContext(class RendererContext* renderer);
		~ImGuiContext() override;

		void Draw();
		void OnImGuiRender() override;

	private:
		ImGuiIO* m_IO;
		RHI::GraphicsContext* m_Graphics;
	};

}
