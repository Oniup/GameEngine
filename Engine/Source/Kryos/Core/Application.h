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
			KY_ASSERT(index < m_Count, "Index overflow {}", "violation");
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
		Application(ApplicationSpecification&& specification);
		 virtual ~Application();

		virtual void OnStart() {}
		void Run();

		template <typename TModule, typename... TArgs>
		static TModule* PushModule(TArgs&&... args)
		{
			m_Modules.emplace(Meta::GetTypeHash<TModule>(), new TModule(std::forward<TArgs>(args)...));
			KY_ASSERT(m_Modules.back().second, "Failed to load");
			return static_cast<TModule*>(m_Modules.back().second);
		}

		template <typename TModule>
		static TModule* GetModule()
		{
			constexpr size_t hash = Meta::GetTypeHash<TModule>();
			for (auto entry : m_Modules)
			{
				if (entry.first == hash)
					return static_cast<TModule*>(entry.second);
			}
			return nullptr;
		}

		template<typename TModule>
		static bool ModuleExists()
		{
			return GetModule<TModule>() != nullptr;
		}

	private:
		ApplicationSpecification m_Secification;
		bool m_Running;
		std::vector<std::pair<size_t, ApplicationModule*>> m_Modules;

		static Application* s_Instance;
	};

}

