#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class Timer
{
public:
	Timer(GLfloat tick) : m_Tick(tick) {}

	void Start();
	void Pause();

	void Reset();
	void Update();
	bool Tick();

	inline void SetTickTime(int sec) { m_Tick = sec; }
private:
	GLfloat m_LastTime = 0;
	GLfloat m_DeltaTime = 0;
	GLfloat m_OverallTime = 0;
	GLfloat m_CurrentTime = 0;

	GLfloat m_Tick = 0;
	GLfloat m_TickTime = 0;

	bool pause = true;
};

