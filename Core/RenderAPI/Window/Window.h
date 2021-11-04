#pragma once
#include "../../glm.h"
#include "../RenderAPI.h"



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
	void SwapBuffer();
	void Use();
};

