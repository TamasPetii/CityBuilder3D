#pragma once
#include "Timer.h"
#include <iostream>

class FrameCounter
{
public:
	FrameCounter();
	~FrameCounter();

	bool Tick();
	void Reset();
	void Update();

	GLuint Get_FPS() { return m_Counter * 2.f; }
	GLfloat Get_DeltaTime() { return 500.f / m_Counter; }
private:
	Timer* m_Timer = nullptr;
	GLuint m_Counter = 0;
};

