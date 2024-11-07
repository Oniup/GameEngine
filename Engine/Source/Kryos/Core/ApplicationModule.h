#pragma once

#include "Kryos/Core/Meta/TypeInfo.h"

namespace Kryos
{

	class ApplicationModule
	{
	public:
		virtual ~ApplicationModule() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
	};

}
