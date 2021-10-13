#include "Window.h"







void Window::init(WindowSettings ws)
{
	if (GlWindowPointer) {
		//Debug::Log("Destroying existing window");
		glfwDestroyWindow(GlWindowPointer);
	}
	windowsettings = ws;
#pragma region Window Hints
	if (windowsettings.Resizeable) glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	else glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);




	switch (windowsettings.WindowMode)
	{
	case WINDOWED:
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		GlWindowPointer = glfwCreateWindow(windowsettings.Size.x, windowsettings.Size.y, windowsettings.Title, NULL, NULL);
		break;
	case BORDERLESS:

		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		GlWindowPointer = glfwCreateWindow(windowsettings.Size.x, windowsettings.Size.y, windowsettings.Title, NULL, NULL);

		break;
	case FULLSCREEN:
		GlWindowPointer = glfwCreateWindow(windowsettings.Size.x, windowsettings.Size.y, windowsettings.Title, glfwGetPrimaryMonitor(), NULL);
		break;
	}
	glfwMakeContextCurrent(GlWindowPointer);
#pragma endregion
#ifdef DEBUG
#pragma region Error Check
	if (!GlWindowPointer) {
		Debug::Error("failed to create OpenGL window.");
		const char* Description;
		int Error = glfwGetError(&Description);
		Debug::Error(std::to_string(Error) + ": " + Description);

		//Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials

		return;
	}
#pragma endregion
#pragma region IMGUI
	ImGui_ImplGlfw_InitForOpenGL(GlWindowPointer, true);
	ImGui_ImplOpenGL3_Init();
#pragma endregion

#endif // DEBUG


}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(GlWindowPointer);
}

void Window::FlushFramebuffer()
{
	glfwSwapBuffers(GlWindowPointer);
}

WindowSettings Window::getWindowSettings() { return windowsettings; }
