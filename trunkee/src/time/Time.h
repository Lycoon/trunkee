#pragma once

#include <SDL.h>

class Time
{
public:
	static Time& Get() { return s_instance; }
	
	void OnFrameStart();
	float GetDeltaTime() const { return m_deltaTime / 1000.0f; }
	long GetTime() const { return SDL_GetTicks64(); }

private:
	Time();
	static Time s_instance;

	long m_deltaTime;
	long m_currentFrame;
};