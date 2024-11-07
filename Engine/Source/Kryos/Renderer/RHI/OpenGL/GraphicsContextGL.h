#pragma once

#include "Kryos/Renderer/RHI/Base/GraphicsContextBase.h"
#include <glm/glm.hpp>
#include <fmt/format.h>

namespace Kryos::RHI
{

	class GraphicsContextGL : public GraphicsContextBase
	{
	public:
		GraphicsContextGL(const glm::ivec2& glVersion = glm::ivec2(3, 0));
		~GraphicsContextGL() override;

		const glm::ivec2& GetMinimumAPIVersion() const { return m_API; }
		const std::string GetGLSLStringVersion() const { return fmt::format("#version 1{}{}", m_API.x, m_API.y); }

		void InitializeOpenGL();

		void InitializePlatformImGui(GLFWwindow* nativeWindow) override;
		void DestroyPlatformImGui() override;
		void PlatformImGuiBeginFrame() override;
		void PlatformImGuiRenderFrame() override;

	private:
		glm::ivec2 m_API;
		bool m_GladInitialized;
	};

	using GraphicsContext = GraphicsContextGL;

}