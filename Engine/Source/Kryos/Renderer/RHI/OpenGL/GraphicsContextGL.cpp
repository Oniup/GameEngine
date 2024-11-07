#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Log.h"
#include "Kryos/Renderer/RHI/OpenGL/GraphicsContextGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
// imgui.h must be in front of the impl files
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace Kryos::RHI
{

	GraphicsContextGL::GraphicsContextGL(const glm::ivec2& glVersion)
		: GraphicsContextBase(), m_API(glVersion), m_GladInitialized(false)
	{
		KY_VERBOSE("Initialized OpenGL Graphics Context");
	}

	void GraphicsContextGL::InitializeOpenGL()
	{
		if (!m_GladInitialized)
		{
			int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			KY_ASSERT(result, "Failed to initialize GLAD, need to initialize glfw window before calling this function");
			m_GladInitialized = true;
			KY_VERBOSE("Initialized OpenGL Context through gladGLLoader");
		}
	}

	GraphicsContextGL::~GraphicsContextGL()
	{
		KY_VERBOSE("Destroying OpenGL Graphics Context");
	}

	void GraphicsContextGL::InitializePlatformImGui(GLFWwindow* window)
	{
		ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
		ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
		ImGui_ImplOpenGL3_Init(GetGLSLStringVersion().c_str());
	}

	void GraphicsContextGL::DestroyPlatformImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void GraphicsContextGL::PlatformImGuiBeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
	}

	void GraphicsContextGL::PlatformImGuiRenderFrame()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}

