#include "Timer.h"

void Timer::Start()
{
	pause = false;
	m_LastTime = (float)glfwGetTime();
}

void Timer::Pause()
{
	pause = true;
}

void Timer::Reset()
{
	pause = false;
	m_OverallTime = 0;
	m_LastTime = (float)glfwGetTime();
}

void Timer::Update()
{
	if (pause) return;

	m_CurrentTime = (float)glfwGetTime();
	m_DeltaTime = m_CurrentTime - m_LastTime;
	m_LastTime = m_CurrentTime;

	m_OverallTime += m_DeltaTime;
	m_TickTime += m_DeltaTime;
}

bool Timer::Tick()
{
	if (m_TickTime >= m_Tick)
	{
		m_TickTime = 0;
		return true && !pause;
	}

	return false;
}
