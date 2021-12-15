#include "Application.h"
//#include "../Modules/Texture/Texture.h"
#include"../RenderAPI/RenderAPI.h"
#include "../Debug/Console.h"

#ifdef IMGUI
ImGuiContext* Application::AppImguiContext;
#endif
bool Application::OpenGlActive = false;

void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
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


#include "../Input/Input.h"
#include "../Debug/Debugger.h"
//#include "../Debug/NewDebugger.h"
#include "../Debug/Gizmos/Gizmos.h"



Window Application::MainWindow;
void Application::init(WindowSettings ws)
{

	InitOpenGL(4, 6);
	
#ifdef IMGUI
	InitImGui();
#endif



	//oldWindow::init(ws);
	MainWindow = Window();
	MainWindow.Use();
	Console::Log("OpenGL " + std::string((const char*)glGetString(GL_VERSION)));

#ifdef OPENGL_DEBUGMODE
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#endif
	


	if (glewInit() != GLEW_OK) Console::Critical("Unable to initialize GLEW");
	else Console::Log("GLEW init");

#ifdef DEBUGGER
	Debugger::getInstance();
	//NewDebugger::GetInstance();
	MainWindow.Use();
#endif

#ifdef OPENGL_DEBUGMODE
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debugMessage, NULL);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif

}




bool Application::ShouldClose()
{
	return MainWindow.ShouldClose();
	//return oldWindow::ShouldClose();
}
void Application::PreRender()
{

}

void Application::PollEvents()
{
	glfwPollEvents();
}



void Application::Terminate() {

	Debugger::getInstance()->ShutDown();
	//NewDebugger::ShutDown();
}


void Application::InitOpenGL(int VersionMajor, int VersionMinor)
{
	
	
	if (!glfwInit())
	{

		//Debug::Error("Failed to initialize GLFW");
		const char* Description;
		int Error = glfwGetError(&Description);
		//Debug::Error(std::to_string(Error) + ": " + Description);
		return;
	}

 // _DEBUG

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VersionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	OpenGlActive = true;




}




