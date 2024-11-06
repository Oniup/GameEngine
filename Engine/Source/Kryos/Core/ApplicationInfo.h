#pragma once

#include "Kryos/Core/Defines.h"
#include <glm/glm.hpp>
#include <string>

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

	struct ApplicationInfo
	{
		std::string Name;
		glm::ivec3 Version;
		std::string WorkingDirectory;
		ApplicationArguments Arguments;
	};

}
