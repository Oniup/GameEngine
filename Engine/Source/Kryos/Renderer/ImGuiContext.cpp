#include "Kryos/Renderer/ImGuiContext.h"
#include "Kryos/Renderer/RendererContext.h"
#include "Kryos/Core/Application.h"
#include <glfw/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace Kryos
{

	ImGuiContext::ImGuiContext(RendererContext* renderer)
		: m_Graphics(&renderer->GetGraphicsContext())
	{
		KY_INFO("Initializing ImGui Context");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		m_IO = &ImGui::GetIO();
		m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
		m_IO->ConfigViewportsNoTaskBarIcon = true;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		m_Graphics->InitializePlatformImGui(renderer->GetMainWindow().GetNative());
		renderer->m_ImGui = this;
	}

	ImGuiContext::~ImGuiContext()
	{
		if (m_IO)
		{
			KY_INFO("Destroying ImGui Context");
			m_Graphics->DestroyPlatformImGui();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

			m_Graphics = nullptr;
			m_IO = nullptr;

			RendererContext* renderer = Application::GetModule<RendererContext>();
			renderer->m_ImGui = nullptr;
		}
	}

	void ImGuiContext::Draw()
	{
		m_Graphics->PlatformImGuiBeginFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (auto& [hash, entry] : Application::GetAllModules())
			entry->OnImGuiRender();

		ImGui::Render();
		m_Graphics->PlatformImGuiRenderFrame();

		if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* mainWindowContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(mainWindowContext);
		}
	}

	void ImGuiContext::OnImGuiRender()
	{
		ImGui::Begin("Test");
		{
            static float f = 0.0f;
            static int counter = 0;
			static glm::vec3 color;

            ImGui::Text("This is some useful text.");               

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            
            ImGui::ColorEdit3("clear color", (float*)&color);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_IO->Framerate, m_IO->Framerate);
			ImGui::End();
		}
	}

}