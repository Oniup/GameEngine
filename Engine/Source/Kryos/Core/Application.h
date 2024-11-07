#pragma once

#include "Kryos/Core/ApplicationInfo.h"
#include "Kryos/Core/ApplicationModule.h"
#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Log.h"
#include "Kryos/Renderer/RendererContext.h"
#include <glm/glm.hpp>
#include <mutex>

namespace Kryos
{
	
	class Application
	{
	public:
		Application(ApplicationInfo&& info);
		virtual ~Application();

		inline static const ApplicationInfo& GetInfo() { return s_Instance->m_Info; }
		inline static std::vector<std::pair<size_t, ApplicationModule*>>& GetAllModules() { return s_Instance->m_Modules; }

		void Run();
		void SetupRequiredModules();

		template <typename TModule, typename... TArgs>
		static TModule* PushModule(TArgs&&... args)
		{
			s_Instance->m_Modules.emplace_back(Meta::GetTypeHash<TModule>(), new TModule(std::forward<TArgs>(args)...));
			KY_ASSERT(s_Instance->m_Modules.back().second, "Failed to load");
			return static_cast<TModule*>(s_Instance->m_Modules.back().second);
		}

		template <typename TModule>
		static TModule* GetModule()
		{
			constexpr size_t hash = Meta::GetTypeHash<TModule>();
			for (auto entry : s_Instance->m_Modules)
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
		ApplicationInfo m_Info;
		std::vector<std::pair<size_t, ApplicationModule*>> m_Modules;
		bool m_Running = true;
		RendererContext* m_Renderer = nullptr;

		static Application* s_Instance;
	};

}

