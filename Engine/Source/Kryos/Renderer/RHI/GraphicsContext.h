#pragma once

#ifdef KY_RENDERER_BACKEND_OPENGL
#	include "Kryos/Renderer/RHI/OpenGL/GraphicsContextGL.h"

#elif KY_RENDERER_BACKEND_VULKAN
#	include "Kryos/Renderer/RHI/Vulkan/GraphicsContextVK.h"
#endif

