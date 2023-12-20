#pragma once

#include "../event/EventManager.h"

#include <glm/glm.hpp>
#include <optional>

enum class KeybindAction
{
	MoveFront,
	MoveBack,
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	MoveFast
};

struct Keybind
{
	Keybind() {}
	Keybind(SDL_Scancode _key): key(_key) {}
	Keybind(SDL_Keymod _mod, SDL_Scancode _key) : mod(_mod), key(_key) {}

	SDL_Keymod mod = KMOD_NONE;
	SDL_Scancode key = SDL_SCANCODE_UNKNOWN;
};

class InputManager
{
public:
	using Keybinds = std::pair<Keybind, Keybind>;
	using KeybindMap = std::unordered_map<KeybindAction, Keybinds>;

	static InputManager& Get() { return s_instance; }

	void SetDefaultKeybinds();
	bool IsActive(KeybindAction action) const;

	inline void SetKeyPressed(int key, bool pressed) { m_pressedKeys[key] = pressed; }
	inline bool IsKeyPressed(int key) const { return m_pressedKeys[key]; }

private:
	InputManager();
	static InputManager s_instance;

	KeybindMap m_keybinds;
	bool m_pressedKeys[284];
};