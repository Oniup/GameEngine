#pragma once

#include <string_view>
#include <glm/glm.hpp> 

struct GLFWwindow;

namespace Kryos
{

	enum WindowOptionFlag
	{
		WindowOptionFlag_Invalid			= 0,
		WindowOptionFlag_FullScreenMode 	= 1 << 0,
		WindowOptionFlag_BorderlessMode 	= 1 << 1,
		WindowOptionFlag_WindowedMode		= 1 << 2,
		WindowOptionFlag_Resizable			= 1 << 3,
		WindowOptionFlag_TransparentBuffer	= 1 << 4,
	};

	struct WindowOptionFlags
	{
		int Flags;

		static constexpr int s_Default = WindowOptionFlag_WindowedMode | WindowOptionFlag_Resizable;

		WindowOptionFlags(int flags = s_Default)
			: Flags(flags) {}


		inline operator int() const { return Flags; }
		inline operator int&() { return Flags; }
	};

	class Window
	{
	public:
		Window(const std::string_view title, int width, int height, WindowOptionFlags flags);
		~Window();

		static bool ValidateFlags(WindowOptionFlags flags);

		inline static glm::ivec2 GetOpenGLVersion() { return glm::ivec2(4, 5); }

		glm::ivec2 GetSize();
		glm::ivec2 GetFrameSize();
		glm::ivec2 GetPosition();

		inline GLFWwindow* GetNative() { return m_Window; }
		inline const GLFWwindow* GetNative() const { return m_Window; }
		inline const WindowOptionFlags& GetFlags() const { return m_Flags; }

		void SwapBuffers();
		void MakeCurrentContext();
		bool IsClosing() const;

	protected:
		GLFWwindow* m_Window;
		WindowOptionFlags m_Flags;
	};

}
