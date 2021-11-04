#pragma once
#include "../RenderAPI/RenderAPI.h"
#include "../Application/Application.h"
#include "Console.h"
#include <thread>
static class NewDebugger
{
public:
	static void DebuggerdebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message, const void* userParam)
	{
		string log = "[OpenGL]: (source: " + std::to_string(source) + string(") ") + message;
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
	static NewDebugger* INSTANCE;
	static NewDebugger* GetInstance();
	static std::thread DebuggerThread;
	static bool ShouldShutdown;;
	static void ShutDown();
public:
	NewDebugger() {
		INSTANCE = this;
	}
	void operator()() const {
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwMakeContextCurrent(MainWindow::GlWindowPointer);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);


		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		int WinSizeX = 600;
		int WinSizeY = 800;
		int MonitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&MonitorCount);
		GLFWwindow* DebugWindowPointer;
		if (MonitorCount > 1) {
			GLFWmonitor* secondmonitor = monitors[1];
			int secXpos, secYpos;
			glfwGetMonitorPos(secondmonitor, &secXpos, &secYpos);
			int secXsize, secYsize;
			const GLFWvidmode* secVideoMode = glfwGetVideoMode(secondmonitor);

			//glfwSetWindowPos(DebugWindowPointer, secXpos + secVideoMode->width / 2 - WinSizeX / 2, secYpos + secVideoMode->height / 2 - WinSizeY / 2);
			DebugWindowPointer = glfwCreateWindow(WinSizeX, WinSizeY, "Interact Debugger", secondmonitor, MainWindow::GlWindowPointer);
			
		}
		else DebugWindowPointer = glfwCreateWindow(WinSizeX, WinSizeY, "Interact Debugger", NULL, MainWindow::GlWindowPointer);
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebuggerdebugMessage, NULL);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

		Console::Log(to_string(glGetError()));
		if (!DebugWindowPointer) {
			assert("failed to create OpenGL window.");
			const char* Description;
			int Error = glfwGetError(&Description);
			std::string errorline = std::to_string(Error) + ": " + Description;
			assert(errorline.c_str());

			//Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials

			return;
		}

		

		glfwMakeContextCurrent(DebugWindowPointer);
		while (!ShouldShutdown) {
			glfwPollEvents();
		}
	}
};

