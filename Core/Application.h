#pragma once
#include "Window.h"

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sstream>
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
static class Application
{
public:
	
	static string GetExecutablePath() {

		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		return std::string(buffer).substr(0, pos);
	}
	
	static void init(WindowSettings ws);
	static void ChangeWindowSettings(WindowSettings ws);
	static bool ShouldClose();

	
	static void PreRender();
#ifdef IMGUI
	static void RenderImGui();
#endif
	static void FlushFrameBuffer();
	static void Terminate();
#ifdef IMGUI
	static void DrawDebug();
#endif
private:
#ifdef IMGUI
	static ImGuiContext* AppImguiContext;
#endif
	static bool OpenGlActive;
	
	static void InitOpenGL(int VersionMinor, int VersionMajor);
	#ifdef IMGUI
	static void InitImGui();
	#endif
	
	
};

