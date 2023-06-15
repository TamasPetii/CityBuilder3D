#include "FrameCounter.h"

/**
 * Constructs a FrameCounter object and initializes its timer with a duration of 0.5 seconds.
 *
 * @returns None
 */
FrameCounter::FrameCounter()
{
	m_Timer = new Timer(0.5);
	m_Timer->Start();
}

/**
 * Destructor for the FrameCounter class.
 * Deletes the timer object.
 *
 * @returns None
 */
FrameCounter::~FrameCounter()
{
	delete m_Timer;
}

/**
 * Advances the frame counter by one tick and returns whether the timer has ticked or not.
 *
 * @returns True if the timer has ticked, false otherwise.
 */
bool FrameCounter::Tick()
{
	return m_Timer->Tick();
}

/**
 * Resets the frame counter to zero.
 *
 * @returns None
 */
void FrameCounter::Reset()
{
	m_Counter = 0;
}

/**
 * Updates the frame counter by incrementing the counter and updating the timer.
 *
 * @param None
 *
 * @returns None
 */
void FrameCounter::Update()
{
	m_Timer->Update();
	m_Counter++;
}