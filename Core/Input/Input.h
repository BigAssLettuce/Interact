#pragma once
#include "../Application/MainWindow.h"
#include "../RenderAPI/RenderAPI.h"
#include "../glm.h"
enum class KeyboardInputs {
	UP = GLFW_KEY_UP,
	DOWN = GLFW_KEY_DOWN,
	LEFT = GLFW_KEY_LEFT,
	RIGHT = GLFW_KEY_RIGHT,

	ESCAPE = GLFW_KEY_ESCAPE,
	TAB = GLFW_KEY_TAB,
	LEFTSHIFT = GLFW_KEY_LEFT_SHIFT,
	LEFTCONTROL = GLFW_KEY_LEFT_CONTROL,
	LEFTALT = GLFW_KEY_LEFT_ALT,

	RIGHTSHIFT = GLFW_KEY_RIGHT_SHIFT,
	

	ONE = GLFW_KEY_1,
	TWO = GLFW_KEY_2,
	THREE = GLFW_KEY_3,

	ZERO =GLFW_KEY_0,

	Q = GLFW_KEY_Q,
	W = GLFW_KEY_W,
	E = GLFW_KEY_E,

	A = GLFW_KEY_A,
	S = GLFW_KEY_S,
	D = GLFW_KEY_D,
	
	Z = GLFW_KEY_Z
};
enum class KeyState {
	PRESS = GLFW_PRESS,
	RELEASE = GLFW_RELEASE
};
class Input
{
	
protected:
	static Input* INSTANCE;
	glm::ivec2 MousePos;
	void MousePosCallback(GLFWwindow* window, double xpos, double ypos);

public:
	static Input* GetInstance();
	Input();

	glm::ivec2 GetMousePos();
	void SetMousePos(glm::vec2 pos) { glfwSetCursorPos(MainWindow::GlWindowPointer, pos.x, pos.y); }

	void SetStickyKeys(bool state) {

		glfwSetInputMode(MainWindow::GlWindowPointer,GLFW_STICKY_KEYS, state);

	}
	KeyState GetKeyState(KeyboardInputs Key) { return (KeyState)glfwGetKey(MainWindow::GlWindowPointer, (int)Key); }

};

