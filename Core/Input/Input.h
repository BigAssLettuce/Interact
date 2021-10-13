#pragma once
#include "../include.h"
enum class KeyboardInputs {
	UP = GLFW_KEY_UP,
	DOWN = GLFW_KEY_DOWN
};
enum class KeyState {
	PRESS = GLFW_PRESS,
	RELEASE = GLFW_RELEASE
};
static class Input
{
public:
	static KeyState GetKeyState(KeyboardInputs Key);
	static vec2 GetMousePos();
	static void SetMousePos(vec2 pos);
};

