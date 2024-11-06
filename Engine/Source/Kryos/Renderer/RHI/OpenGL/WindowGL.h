#pragma once

#include "Kryos/Renderer/RHI/Base/WindowBase.h"
#include "Kryos/Renderer/RHI/GraphicsContext.h"

#if defined(KY_RENDERER_BACKEND_OPENGL)

namespace Kryos::RHI
{

	class WindowGL : public WindowBase
	{
	public:
		WindowGL(GraphicsContextGL* context, const std::string_view title, int width, int height, WindowOptionFlags flags);
		~WindowGL() override;
	};

	using Window = WindowGL;

}

#endif
