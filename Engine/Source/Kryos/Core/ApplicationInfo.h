#pragma once

#include "Kryos/Core/Defines.h"
#include <string>
#include <glm/glm.hpp>

namespace Kryos
{

	class ApplicationArguments
	{
	public:
		KY_FORCE_INLINE ApplicationArguments(const int count, char** args)
			: m_Count(count), m_Args(args) {}

		KY_FORCE_INLINE int Count() const { return m_Count; }

		KY_FORCE_INLINE const char* operator[](const int index) const
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
