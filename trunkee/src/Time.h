#pragma once

#include <SDL.h>

class Time {
public:
	static void Update();
	static float GetDeltaTime() { return m_deltaTime; }
	static float GetTime() { return 0; }

private:
	static float m_deltaTime;
	static float m_lastFrame;
};