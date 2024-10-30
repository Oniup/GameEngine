#include "Kryos/Core/Application.h"

namespace Kryos
{

	Application::Application(ApplicationSpecification&& specification)
		: m_Secification(std::move(specification)), m_Running(true)
	{
	}

	Application::~Application()
	{
		for (auto entry : m_Modules)
			delete entry.second;
	}

	void Application::Run()
	{
	}

}