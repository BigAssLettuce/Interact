#include "Window.h"
#include "../../Application/MainWindow.h"
void Window::Init()
{
	if (!WindowResizeable)glfwWindowHint(GLFW_RESIZABLE, false);
	//else glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	if (WindowBorderless)glfwWindowHint(GLFW_DECORATED, false);
	//else glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	if (WindowFloating)glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	if (WindowTransparent)glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	GLFWwindow* MainContext = NULL;
	if (WindowContextShared)MainContext = MainWindow::GlWindowPointer;


	GLWindowPointer = glfwCreateWindow(WindowSize.x, WindowSize.y, WindowTitle, NULL, MainContext);

}

Window::Window()
{
	Init();
}

void Window::SwapBuffer()
{
	glfwSwapBuffers(GLWindowPointer);
}

void Window::Use()
{
	glfwMakeContextCurrent(GLWindowPointer);
}


