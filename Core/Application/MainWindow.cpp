#include "MainWindow.h"
#include "../RenderAPI/RenderAPI.h"
#include "../Debug/Console.h"
WindowSettings MainWindow::windowsettings = WindowSettings();
GLFWwindow* MainWindow::GlWindowPointer;






void MainWindow::NewFrame(bool ClearColor)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	if (ClearColor) glClear(GL_COLOR_BUFFER_BIT);
}

void MainWindow::init(WindowSettings ws)
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

#pragma region Error Check
	if (!GlWindowPointer) {
		Console::Error("failed to create OpenGL window.");
		const char* Description;
		int Error = glfwGetError(&Description);
		Console::Error(std::to_string(Error) + ": " + Description);

		//Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials

		return;
	}
#pragma endregion

#ifdef IMGUI
#pragma region IMGUI
	ImGui_ImplGlfw_InitForOpenGL(GlWindowPointer, true);
	ImGui_ImplOpenGL3_Init();
#pragma endregion
#endif

}

bool MainWindow::ShouldClose()
{
	return glfwWindowShouldClose(GlWindowPointer);
}

void MainWindow::SetShouldClose(bool close)
{
	glfwSetWindowShouldClose(GlWindowPointer, close);
}

void MainWindow::FlushFramebuffer()
{
	glfwSwapBuffers(GlWindowPointer);
}

WindowSettings MainWindow::getWindowSettings() { return windowsettings; }
