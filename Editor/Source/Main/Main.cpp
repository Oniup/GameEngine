#include "Main/Main.h"
#include <Kryos/Renderer/RendererContext.h>
#include <Kryos/Core/EntryPoint.h>
#include <Kryos/Renderer/ImGuiContext.h>
#include <Kryos/Core/Log.h>
#include <filesystem>
#include <iostream>

KryosEditor::KryosEditor(Kryos::ApplicationInfo&& info) 
	: Kryos::Application(std::move(info))
{
	Kryos::Log* log = PushModule<Kryos::Log>();
#ifndef KY_DIST
	log->PushOutput(new Kryos::TerminalLogOutput(Kryos::LogSeverity_None));
#endif

	SetupRequiredModules();
	// PushModule<Kryos::ImGuiContext>(*m_Renderer);
}

Kryos::Application* CreateApplication(int argc, char** argv)
{
	return new KryosEditor(Kryos::ApplicationInfo {
		.Name				= "Kryos Editor",
		.Version			= glm::ivec3(KY_VERSION_MAJOR, KY_VERSION_MINOR, KY_VERSION_PATCH),
		.WorkingDirectory	= "",
		.Arguments			= Kryos::ApplicationArguments(argc, argv),
	});
}
