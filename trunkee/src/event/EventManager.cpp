#include "EventManager.h"
#include "../input/InputManager.h"

#include <iostream>

EventManager EventManager::s_instance = EventManager();

void EventManager::Poll(bool& needsQuit)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			OnQuit();
			needsQuit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.repeat != 0)
				return;
			OnKeyDown(e.key);
		}
		else if (e.type == SDL_KEYUP)
			OnKeyUp(e.key);
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			OnMouseClick(e.button);
		else if (e.type == SDL_MOUSEBUTTONUP)
			OnMouseRelease(e.button);
		else if (e.type == SDL_MOUSEMOTION)
			OnMouseMove(e.motion);
		else if (e.type == SDL_MOUSEWHEEL)
			OnMouseWheel(e.wheel);
		else if (e.type == SDL_WINDOWEVENT)
			OnWindowEvent(e.window);
	}
}

void EventManager::AddListener(Listener listener, EventType type)
{
	m_listeners[type].push_back(listener);
}

void EventManager::OnQuit()
{
	for (Listener& listener : m_listeners[EventType::ProgramQuit])
		listener({});
}

void EventManager::OnKeyDown(const SDL_KeyboardEvent& e)
{
	InputManager::Get().SetKeyPressed(e.keysym.scancode, true);
	for (Listener& listener : m_listeners[EventType::KeyDown])
		listener({ e });
}

void EventManager::OnKeyUp(const SDL_KeyboardEvent& e)
{
	InputManager::Get().SetKeyPressed(e.keysym.scancode, false);
	for (Listener& listener : m_listeners[EventType::KeyUp])
		listener({ e });
}

void EventManager::OnMouseClick(const SDL_MouseButtonEvent& e)
{
	for (Listener& listener : m_listeners[EventType::MouseClick])
		listener({ e });
}

void EventManager::OnMouseRelease(const SDL_MouseButtonEvent& e)
{
	for (Listener& listener : m_listeners[EventType::MouseRelease])
		listener({ e });
}

void EventManager::OnMouseMove(const SDL_MouseMotionEvent& e)
{
	for (Listener& listener : m_listeners[EventType::MouseMove])
		listener({ e });
}

void EventManager::OnMouseWheel(const SDL_MouseWheelEvent& e)
{
	for (Listener& listener : m_listeners[EventType::MouseWheel])
		listener({ e });
}

void EventManager::OnWindowEvent(const SDL_WindowEvent& e)
{
	for (Listener& listener : m_listeners[EventType::WindowEvent])
		listener({ e });

	if (e.event == SDL_WINDOWEVENT_RESIZED)
		for (Listener& listener : m_listeners[EventType::WindowResize])
			listener({ e });
	else if (e.event == SDL_WINDOWEVENT_CLOSE)
		for (Listener& listener : m_listeners[EventType::WindowClosed])
			listener({ e });
}