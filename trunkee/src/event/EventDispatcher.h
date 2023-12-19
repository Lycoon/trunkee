#pragma once

/*
#include "EventManager.h"

template <typename EventData>
class EventDispatcher
{
	using Listener = EventManager::Listener<EventData>;
	using ListenerList = std::vector<Listener<EventData>>;

public:
	void Dispatch(const EventData& e);
	void AddListener(Listener<EventData> listener);

private:
	ListenerList m_listeners;
};
*/