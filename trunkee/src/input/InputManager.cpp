#include "InputManager.h"

InputManager InputManager::s_instance = InputManager();
InputManager::InputManager()
{
	SetDefaultKeybinds();

	for (int i = 0; i < 284; ++i)
		m_pressedKeys[i] = false;
}

bool InputManager::IsActive(KeybindAction action) const
{
	const Keybinds& keybinds = m_keybinds.at(action);
	return m_pressedKeys[keybinds.first.key] || m_pressedKeys[keybinds.second.key];
}

void InputManager::SetDefaultKeybinds()
{
	m_keybinds[KeybindAction::MOVE_FRONT] = { { SDL_SCANCODE_W },	   { SDL_SCANCODE_UP } };
	m_keybinds[KeybindAction::MOVE_BACK]  = { { SDL_SCANCODE_S },	   { SDL_SCANCODE_DOWN } };
	m_keybinds[KeybindAction::MOVE_LEFT]  = { { SDL_SCANCODE_A },	   { SDL_SCANCODE_LEFT } };
	m_keybinds[KeybindAction::MOVE_RIGHT] = { { SDL_SCANCODE_D },	   { SDL_SCANCODE_RIGHT } };
	m_keybinds[KeybindAction::MOVE_UP]    = { { SDL_SCANCODE_SPACE },  { SDL_SCANCODE_UNKNOWN } };
	m_keybinds[KeybindAction::MOVE_DOWN]  = { { SDL_SCANCODE_LCTRL },  { SDL_SCANCODE_UNKNOWN } };
	m_keybinds[KeybindAction::MOVE_FAST]  = { { SDL_SCANCODE_LSHIFT }, { SDL_SCANCODE_UNKNOWN } };
}