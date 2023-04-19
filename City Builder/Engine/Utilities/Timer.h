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

	inline void SetTickTime(GLfloat sec) { m_Tick = sec; }

	GLfloat Get_DeltaTime() { return m_DeltaTime; }
private:
	GLfloat m_LastTime = 0.f;
	GLfloat m_DeltaTime = 0.f;
	GLfloat m_OverallTime = 0.f;
	GLfloat m_CurrentTime = 0.f;

	GLfloat m_Tick = 0.f;
	GLfloat m_TickTime = 0.f;

	bool pause = true;
};

