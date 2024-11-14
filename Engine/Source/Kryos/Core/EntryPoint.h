#pragma once

#include "Kryos/Core/Application.h"

extern Kryos::Application* CreateApplication(int argc, char** argv);
bool g_AppRunning = true;

namespace Kryos
{

	int Main(int argc, char** argv)
	{
		Kryos::Application* app = CreateApplication(argc, argv);
		app->Run();
		delete app;
		return 0;
	}

}

#ifdef KY_DIST
#ifdef _WIN32

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Kryos::Main(__argc, __argv);
}

#else
#error "Currently only supports windows"
#endif
#else

int main(int argc, char** argv) 
{
	return Kryos::Main(argc, argv);
}

#endif
