#include "Input.h"
#include "../Window.h"
#include "../Application.h"
KeyState Input::GetKeyState(KeyboardInputs Key)
{


	
	return (KeyState)glfwGetKey(Application::MainWindow.GlWindowPointer,(int)Key);
}
