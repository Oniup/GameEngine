#pragma once

#include "Kryos/Core/Time.h"
#include "Kryos/Core/Meta/TypeInfo.h"

namespace Kryos
{

	class ApplicationModule
	{
	public:
		virtual ~ApplicationModule() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(const Time& time) {}
		virtual void OnImGuiRender() {}
	};

}
