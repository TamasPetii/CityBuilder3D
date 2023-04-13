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
	m_OverallTime = 0;
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
	if (pause) return false;

	if (m_TickTime >= m_Tick)
	{
		m_TickTime = 0;
		return true;
	}

	return false;
}
