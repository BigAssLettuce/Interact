#include "Window.h"

#include "../Debug/Console.h"
#include "../Application/Application.h"
void WindowdebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::string log = "[OpenGL]: (source: " + std::to_string(source) + std::string(") ") + message;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		Console::Critical(log);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		Console::Error(log);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		Console::Warning(log);
		break;
#ifdef OPENGL_DEBUGMODE_SEVERITY_ALL

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		Console::Log(log);
		break; //NOTIFICATIONS ARE ACTUAL NOTIFICATIONS. USUALLY NOT IMPORTANT
#endif

	}


}

void Window::Init()
{

	if (!Application::GetIsOpenGLInit()) return;
#ifdef OPENGL_DEBUGMODE
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#endif
	if (!WindowResizeable)glfwWindowHint(GLFW_RESIZABLE, false);
	//else glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	if (WindowBorderless)glfwWindowHint(GLFW_DECORATED, false);
	//else glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	if (WindowFloating)glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	if (WindowTransparent)glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	GLFWwindow* MainContext = NULL;
	if (WindowContextShared)MainContext = Application::MainWindow.GLWindowPointer;


	GLWindowPointer = glfwCreateWindow(WindowSize.x, WindowSize.y, WindowTitle, NULL, MainContext);

#ifdef OPENGL_DEBUGMODE
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//glDebugMessageCallback(WindowdebugMessage, NULL);

	//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif

}

Window::Window()
{
	Init();
}

void Window::Resize(int x, int y)
{
	glViewport(0, 0, x, y);
	glfwSetWindowSize(GLWindowPointer, x, y);
	WindowSize.x = x;
	WindowSize.y = y;
}

void Window::SwapBuffer()
{
	glfwSwapBuffers(GLWindowPointer);
}

void Window::Use()
{
	glfwMakeContextCurrent(GLWindowPointer);
}

void Window::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}


