#pragma once

#include "Oniun/Core/Time.h"

namespace Oniun
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
