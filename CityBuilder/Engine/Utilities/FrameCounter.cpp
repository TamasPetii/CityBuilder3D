#include "FrameCounter.h"

FrameCounter::FrameCounter()
{
	m_Timer = new Timer(0.5);
	m_Timer->Start();
}

FrameCounter::~FrameCounter()
{
	delete m_Timer;
}

bool FrameCounter::Tick()
{
	return m_Timer->Tick();
}

void FrameCounter::Reset()
{
	m_Counter = 0;
}

void FrameCounter::Update()
{
	m_Timer->Update();
	m_Counter++;
}