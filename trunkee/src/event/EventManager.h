#pragma once

#include <SDL_Events.h>

#include <unordered_map>
#include <functional>
#include <variant>

#include "EventDispatcher.h"

enum class EventType
{
	ProgramQuit,

	WindowEvent,
	WindowResize,
	WindowHidden,
	WindowShown,
	WindowExposed,
	WindowMoved,
	WindowMinimized,
	WindowMaximized,
	WindowClosed,

	KeyDown,
	KeyUp,

	MouseClick,
	MouseRelease,
	MouseMove,
	MouseWheel
};

class EventManager
{
public:
	union EventData
	{
		SDL_WindowEvent window;
		SDL_KeyboardEvent key;
		SDL_MouseButtonEvent mouseButton;
		SDL_MouseMotionEvent mouseMotion;
		SDL_MouseWheelEvent mouseWheel;

		EventData() {}
		EventData(const SDL_WindowEvent& e) : window(e) {}
		EventData(const SDL_KeyboardEvent& e) : key(e) {}
		EventData(const SDL_MouseButtonEvent& e) : mouseButton(e) {}
		EventData(const SDL_MouseMotionEvent& e) : mouseMotion(e) {}
		EventData(const SDL_MouseWheelEvent& e) : mouseWheel(e) {}
	};

	static EventManager& Get() { return s_instance; }

	using Listener = std::function<void(const EventData&)>;
	using ListenerMap = std::unordered_map<EventType, std::vector<Listener>>;

	void Poll(bool& needsQuit);
	void AddListener(Listener listener, EventType type);

private:
	void OnQuit();
	void OnWindowEvent(const SDL_WindowEvent& e);
	void OnKeyDown(const SDL_KeyboardEvent& e);
	void OnKeyUp(const SDL_KeyboardEvent& e);
	void OnMouseClick(const SDL_MouseButtonEvent& e);
	void OnMouseRelease(const SDL_MouseButtonEvent& e);
	void OnMouseMove(const SDL_MouseMotionEvent& e);
	void OnMouseWheel(const SDL_MouseWheelEvent& e);

	ListenerMap m_listeners;

	static EventManager s_instance;
};
