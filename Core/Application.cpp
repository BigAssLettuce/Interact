#include "Application.h"

bool Application::OpenGlActive = false;
Window Application::MainWindow;

#ifdef DEBUG
void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	string log = "OpenGL Error: (source: " + std::to_string(source) + string(") ") + message;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		Debug::Critical(log);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		Debug::Error(log);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		Debug::Warning(log);
		break;
		/*
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		Debug::Log(log);
		break;*/ //NOTIFICATIONS ARE ACTUAL NOTIFICATIONS. USUALLY NOT IMPORTANT
	}


}
#endif // DEBUG


void Application::init(WindowSettings ws)
{
	InitOpenGL(4, 5);
	
	#ifdef DEBUG
	InitImGui();
	#endif
	
	
	MainWindow = Window();
	MainWindow.init(ws);

	Debug::Log("OpenGL " + std::string((const char*)glGetString(GL_VERSION)));

	if (glewInit() != GLEW_OK) Debug::Critical("Unable to initialize GLEW");
	else Debug::Log("GLEW init");
	
	
	#ifdef DEBUG

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debugMessage, NULL);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	ImGui::StyleColorsDark();
	#endif 

}

#ifdef DEBUG

void Application::InitImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

}
#endif // _DEBUG
bool Application::ShouldClose()
{
	return MainWindow.ShouldClose();
}
void Application::PreRender()
{

#ifdef DEBUG
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif // _DEBUG


}
void Application::RenderImGui()
{
#ifdef DEBUG
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void Application::FlushFrameBuffer()
{
	MainWindow.FlushFramebuffer();


}

void Application::Terminate() {
#ifdef DEBUG
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG

}

void Application::InitOpenGL(int VersionMinor, int VersionMajor)
{
	if (!glfwInit())
	{

		//Debug::Error("Failed to initialize GLFW");
		const char* Description;
		int Error = glfwGetError(&Description);
		//Debug::Error(std::to_string(Error) + ": " + Description);
		return;
	}
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#endif // _DEBUG

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VersionMinor); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VersionMajor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	OpenGlActive = true;
	



}




