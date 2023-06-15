#include "Timer.h"

/**
 * Starts the timer by setting the pause flag to false and initializing the last time to the current time.
 *
 * @returns None
 */
void Timer::Start()
{
	pause = false;
	m_LastTime = (float)glfwGetTime();
}

/**
 * Pauses the timer.
 *
 * @returns None
 */
void Timer::Pause()
{
	pause = true;
}

/**
 * Resets the timer by setting the pause flag to false and resetting the overall time and last time.
 *
 * @returns None
 */
void Timer::Reset()
{
	pause = false;
	m_OverallTime = 0;
	m_LastTime = (float)glfwGetTime();
}

/**
 * Updates the timer by calculating the elapsed time since the last update.
 * If the timer is paused, no update is performed.
 *
 * @returns None
 */
void Timer::Update()
{
	if (pause) return;

	m_CurrentTime = (float)glfwGetTime();
	m_DeltaTime = m_CurrentTime - m_LastTime;
	m_LastTime = m_CurrentTime;

	m_OverallTime += m_DeltaTime;
	m_TickTime += m_DeltaTime;
}

/**
 * Checks if the timer has reached the tick interval and returns true if it has.
 *
 * @returns True if the timer has reached the tick interval and is not paused, false otherwise.
 */
bool Timer::Tick()
{
	if (m_TickTime >= m_Tick)
	{
		m_TickTime = 0;
		return true && !pause;
	}

	return false;
}
