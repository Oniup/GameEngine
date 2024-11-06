#pragma once

namespace Kryos::RHI
{

	class GraphicsContextBase
	{
	public:
		GraphicsContextBase();
		virtual ~GraphicsContextBase();

		virtual void Initialize() {}
		virtual void Destroy() {}
	};

}
