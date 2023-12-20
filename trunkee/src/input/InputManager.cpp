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
	m_keybinds[KeybindAction::MoveFront] = { { SDL_SCANCODE_W },	   { SDL_SCANCODE_UP } };
	m_keybinds[KeybindAction::MoveBack]  = { { SDL_SCANCODE_S },	   { SDL_SCANCODE_DOWN } };
	m_keybinds[KeybindAction::MoveLeft]  = { { SDL_SCANCODE_A },	   { SDL_SCANCODE_LEFT } };
	m_keybinds[KeybindAction::MoveRight] = { { SDL_SCANCODE_D },	   { SDL_SCANCODE_RIGHT } };
	m_keybinds[KeybindAction::MoveUp]    = { { SDL_SCANCODE_SPACE },   { SDL_SCANCODE_UNKNOWN } };
	m_keybinds[KeybindAction::MoveDown]  = { { SDL_SCANCODE_LCTRL },   { SDL_SCANCODE_UNKNOWN } };
	m_keybinds[KeybindAction::MoveFast]  = { { SDL_SCANCODE_LSHIFT },  { SDL_SCANCODE_UNKNOWN } };
}