#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include <imgui/imgui.h>

namespace Kryos
{

	class ImGuiContext : public ApplicationModule
	{
	public:
		ImGuiContext(class RendererContext& renderer);
		~ImGuiContext() override;

		void Draw(class RendererContext& renderer);
		void OnImGuiRender() override;

	private:
		ImGuiIO* m_IO;
	};

}
