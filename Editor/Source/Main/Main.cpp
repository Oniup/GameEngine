#define GLFW_INCLUDE_NONE

#include "Main/Main.h"
#include <Kryos/Core/Log.h>
#include <iostream>

// - Start renderer module implementation and window handle
// - Start ImGui module 

KryosEditor::KryosEditor(Kryos::ApplicationSpecification&& specification) 
	: Kryos::Application(std::move(specification))
{
	Kryos::Log* log = PushModule<Kryos::Log>();
	log->PushOutput(new Kryos::TerminalLogOutput(Kryos::LogSeverity_None));

	KY_INFO("Test info message");
	KY_TRACE("Test trace message");
	KY_VERBOSE("Test verbose message");
	KY_WARNING("Test warning message");
	KY_ERROR("Test error message");
	KY_FATAL("Test fatal message");

	SetupRequiredModules();
}

int main(int argc, char** argv)
{
	KryosEditor editor(Kryos::ApplicationSpecification {
		.Name				= "Kryos Editor",
		.Version			= glm::ivec3(KY_VERSION_MAJOR, KY_VERSION_MINOR, KY_VERSION_PATCH),
		.WorkingDirectory	= "",
		.Arguments			= Kryos::ApplicationArguments(argc, argv),
	});
	editor.Run();
	return 0;
}
