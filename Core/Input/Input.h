#pragma once
#include "../include.h"
#include "../Window.h"
enum class KeyboardInputs {
	UP = GLFW_KEY_UP,
	DOWN = GLFW_KEY_DOWN
};
enum class KeyState {
	PRESS = GLFW_PRESS,
	RELEASE = GLFW_RELEASE
};
class Input
{
	
protected:
	static Input* INSTANCE;
	ivec2 MousePos;
	void MousePosCallback(GLFWwindow* window, double xpos, double ypos);

public:
	static Input* GetInstance();
	Input();
	ivec2 GetMousePos();
	KeyState GetKeyState(KeyboardInputs Key) {return (KeyState)glfwGetKey(Window::GlWindowPointer, (int)Key);}
	void SetMousePos(vec2 pos) { glfwSetCursorPos(Window::GlWindowPointer, pos.x, pos.y); }
};

