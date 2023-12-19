#include "Time.h"

Time Time::s_instance = Time();
Time::Time()
{
	m_deltaTime = 0; 
	m_currentFrame = GetTime(); 
}

void Time::OnFrameStart() 
{ 
	m_deltaTime = GetTime() - m_currentFrame; 
	m_currentFrame = GetTime(); 
}