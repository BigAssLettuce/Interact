#pragma once
#include "Window.h"
static class Application
{
public:

	static void init(WindowSettings ws);
	static void ChangeWindowSettings(WindowSettings ws);
	static bool ShouldClose();

	
	static void PreRender();
#ifdef IMGUI
	static void RenderImGui();
#endif
	static void FlushFrameBuffer();
	static void Terminate();
	static void DrawDebug();
private:
	static ImGuiContext* AppImguiContext;

	static bool OpenGlActive;
	
	static void InitOpenGL(int VersionMinor, int VersionMajor);
	#ifdef IMGUI
	static void InitImGui();
	#endif
	
	
};

