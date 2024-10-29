#include "Time.h"
#include <GLFW/glfw3.h>

namespace Oniun
{

	float Time::s_LastTime = 0.0f;
	float Time::s_DeltaTime = 0.0f;

	void Time::UpdateDeltaTime()
	{
		float time = GetSeconds();
		s_DeltaTime = time - s_LastTime;
		s_LastTime = time;
	}

	float Time::GetSeconds()
	{
		return glfwGetTime();
	}

	Timer::Timer()
		: m_Start(Time::GetSeconds())
	{
	}

	void Timer::Reset()
	{
		m_Start = Time::GetSeconds();
	}

	float Timer::Elapsed()
	{
		return Time::GetSeconds() - m_Start;
	}

	float Timer::ElapsedMilliseconds()
	{
		return Elapsed() * 1000.0f;
	}

}
