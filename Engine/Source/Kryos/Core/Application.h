#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include "Kryos/Core/Defines.h"
#include <glm/glm.hpp>
#include <mutex>

namespace Kryos
{

	class ApplicationArguments
	{
	public:
		KY_FORCE_INLINE ApplicationArguments(int count, char** args)
			: m_Count(count), m_Args(args) {}

		KY_FORCE_INLINE int Count() { return m_Count; }

		KY_FORCE_INLINE const char* operator[](int index) const
		{
			KY_ASSERT(index < m_Count, "Index overflow violation");
			return m_Args[index];
		}

	private:
		int m_Count = 0;
		char** m_Args = nullptr;
	};

	struct ApplicationSpecification
	{
		std::string Name;
		glm::ivec3 Version;
		std::string WorkingDirectory;
		ApplicationArguments Arguments;
	};
	
	class Application
	{
	public:
		Application(ApplicationSpecification&& info);
		virtual ~Application();

		virtual void OnStart() = 0;

		void Run();

		template <typename TModule, typename... TArgs>
		static TModule* PushModule(TArgs&&... args)
		{
		}

		template <typename TModule>
		static TModule* GetModule()
		{
			for (ApplicationModule* module : m_Modules)
			{
			}
		}

	private:
		ApplicationSpecification m_Secification;
		bool m_Running = true;
		std::vector<ApplicationModule*> m_Modules;
		std::mutex m_MainThread;

		static Application* s_Instance;
	};

}

