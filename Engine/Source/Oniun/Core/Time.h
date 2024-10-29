#pragma once

namespace Oniun
{

	class Time
	{
	public:
		static void UpdateDeltaTime();

		static float GetSeconds();
		static inline float GetMilliseconds() { return GetSeconds() * 1000.0f; }
		static inline float DeltaTime() { return s_DeltaTime; }

	private:
		static float s_LastTime;
		static float s_DeltaTime;
	};

	class Timer
	{
	public:
		Timer();

		void Reset();
		float Elapsed();
		float ElapsedMilliseconds();

	private:
		float m_Start = 0.0f;
	};

}