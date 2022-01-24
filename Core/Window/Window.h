#pragma once
#include "../glm.h"
#include "../RenderAPI/RenderAPI.h"



class Window
{
	const char* WindowTitle = "Default Title";
	glm::vec2 WindowSize = glm::vec2(250, 250);
	bool WindowBorderless = false;
	bool WindowResizeable = true;
	bool WindowFloating = false;
	bool WindowTransparent = false;
	bool WindowContextShared = true;

	


	void Init();
public:
	GLFWwindow* GLWindowPointer;
	Window();
	void Resize(int x, int y);
	void SwapBuffer();
	void Use();
	bool ShouldClose() { return glfwWindowShouldClose(GLWindowPointer); }
	void SetShouldClose(bool State) { glfwSetWindowShouldClose(GLWindowPointer, State); }
	void ClearDepth();
	void Focus() { glfwFocusWindow(GLWindowPointer); }
	glm::vec2 GetWindowSize() { return WindowSize; }
};

