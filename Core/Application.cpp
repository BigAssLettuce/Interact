#include "Application.h"
#include "../Modules/Texture/Texture.h"

ImGuiContext* Application::AppImguiContext;
bool Application::OpenGlActive = false;

void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	string log = "OpenGL Error: (source: " + std::to_string(source) + string(") ") + message;
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
		/*
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		Debug::Log(log);
		break;*/ //NOTIFICATIONS ARE ACTUAL NOTIFICATIONS. USUALLY NOT IMPORTANT
	}


}


#include "Input/Input.h"
#include "Debug/DebugContext.h"
void Application::init(WindowSettings ws)
{

	InitOpenGL(4, 5);

#ifdef IMGUI
	InitImGui();
#endif


	Window();
	Window::init(ws);

	Console::Log("OpenGL " + std::string((const char*)glGetString(GL_VERSION)));

	if (glewInit() != GLEW_OK) Console::Critical("Unable to initialize GLEW");
	else Console::Log("GLEW init");

#ifdef DEBUGWINDOW
	DebugContext::getInstance();
	glfwMakeContextCurrent(Window::GlWindowPointer);
#endif

#ifdef GLDEBUGMODE
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debugMessage, NULL);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif
	//Input = Input();
}


#ifdef IMGUI
void Application::InitImGui() {
	IMGUI_CHECKVERSION();
	AppImguiContext = ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	
}
#endif
bool Application::ShouldClose()
{
	return Window::ShouldClose();
}
void Application::PreRender()
{
	
#ifdef IMGUI
	ImGui::SetCurrentContext(AppImguiContext);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif


}
#ifdef IMGUI
void Application::RenderImGui()
{

	ImGui::ShowDemoWindow();
	Console::DrawImguiConsole();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
#endif
void Application::FlushFrameBuffer()
{
#ifdef IMGUI
	Application::RenderImGui();
#endif
	Window::FlushFramebuffer();


}

void Application::Terminate() {
#ifdef IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif

}
#include "../Modules/Mesh/Mesh.h"
void Application::DrawDebug()
{
	static bool open = true;
	const float PAD = 10.0f;
	static int corner = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
		window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
		window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
		window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		window_flags |= ImGuiWindowFlags_NoMove;
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Debug Menu", &open, window_flags))
	{
		ImGui::Text("Debug Menu");
		ImGui::Separator();
		ImGui::Text("FPS: ");
		ImGui::SameLine();
		ImGui::Text(to_string(io.Framerate).c_str());

		ImGui::Text("Drawcalls");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.f,%.f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		ImGui::Separator();
		if (ImGui::Button("Actions")) {

		}

		ImGui::SameLine();
		static bool Debug_textures = false;
		static bool Debug_mesh3D = false;
		if (ImGui::Button("Debug")) ImGui::OpenPopup("DebugMenu");

		if (ImGui::BeginPopup("DebugMenu")) {
			ImGui::MenuItem("Textures", NULL, &Debug_textures);
			ImGui::MenuItem("Mesh3D", NULL, &Debug_mesh3D);
			ImGui::EndPopup();
		}

		if (Debug_textures) Texture::DrawDebugMenu(&Debug_textures);
		if (Debug_mesh3D) Mesh3D::DrawDebugMenu(&Debug_mesh3D);


		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
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

#ifdef GLDEBUGMODE
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#endif // _DEBUG

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VersionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	OpenGlActive = true;




}




