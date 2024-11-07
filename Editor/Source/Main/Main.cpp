#include "Main/Main.h"
#include <Kryos/Core/Log.h>
#include <Kryos/Renderer/RHI/WindowBase.h>
#include <Kryos/Renderer/RendererContext.h>
#include <Kryos/Renderer/ImGuiContext.h>
#include <iostream>

KryosEditor::KryosEditor(Kryos::ApplicationInfo&& info) 
	: Kryos::Application(std::move(info))
{
	Kryos::Log* log = PushModule<Kryos::Log>();
	log->PushOutput(new Kryos::TerminalLogOutput(Kryos::LogSeverity_None));

	SetupRequiredModules();

	PushModule<Kryos::ImGuiContext>(GetModule<Kryos::RendererContext>());
}

int main(int argc, char** argv)
{
	KryosEditor editor(Kryos::ApplicationInfo {
		.Name				= "Kryos Editor",
		.Version			= glm::ivec3(KY_VERSION_MAJOR, KY_VERSION_MINOR, KY_VERSION_PATCH),
		.WorkingDirectory	= "",
		.Arguments			= Kryos::ApplicationArguments(argc, argv),
	});
	editor.Run();
	return 0;
}
