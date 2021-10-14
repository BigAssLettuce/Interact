#include "Input.h"
//ivec2 Input::MousePos = ivec2(0, 0);
Input* Input::INSTANCE;
ivec2 Input::GetMousePos() {
	return MousePos;
}
//void Input::MousePosCallback(GLFWwindow* window, double xpos, double ypos) { MousePos.x = xpos; MousePos.y = ypos; }
Input::Input() {
	//glfwSetCursorPosCallback(Window::GlWindowPointer, MousePosCallback);
}

Input* Input::GetInstance() {
	if (!INSTANCE) INSTANCE = new Input();
	return INSTANCE;
}