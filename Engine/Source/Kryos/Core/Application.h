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
			return static_cast<TModule*>(s_Instance->m_Modules.back().second);
		}

		template <typename TModule>
		static TModule* GetModule()
		{
			constexpr size_t targetHash = Meta::GetTypeHash<TModule>();
			for (auto& [hash, module] : s_Instance->m_Modules)
			{
				if (hash == targetHash)
					return static_cast<TModule*>(module);
			}
			return nullptr;
		}

		template<typename TModule>
		static bool ModuleExists()
		{
			return GetModule<TModule>() != nullptr;
		}

	protected:
		bool m_Running = true;
		ApplicationInfo m_Info;
		std::vector<std::pair<size_t, ApplicationModule*>> m_Modules;
		RendererContext* m_Renderer = nullptr;

	private:
		static Application* s_Instance;
	};

}

