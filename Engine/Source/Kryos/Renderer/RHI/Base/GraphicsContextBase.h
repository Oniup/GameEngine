#pragma once

struct GLFWwindow;

namespace Kryos::RHI
{

	class GraphicsContextBase
	{
	public:
		GraphicsContextBase();
		virtual ~GraphicsContextBase();

		virtual void Initialize() {}
		virtual void Destroy() {}

		virtual void InitializePlatformImGui(GLFWwindow* window) = 0;
		virtual void DestroyPlatformImGui() = 0;
		virtual void PlatformImGuiBeginFrame() = 0;
		virtual void PlatformImGuiRenderFrame() = 0;
	};

}
