#pragma once
#include "MainWindow.h"
#include "../RenderAPI/Window/Window.h"
#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sstream>
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
class Debugger;
static class Application
{
	friend Debugger;
public:
	
	static const char* GetExecutablePath() {

		char buffer[MAX_PATH];
		::GetSystemDirectoryA(buffer, MAX_PATH);
		//std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		return buffer;
	}
	
	static void init(WindowSettings ws);
	static void ChangeWindowSettings(WindowSettings ws);
	static bool ShouldClose();

	
	static void PreRender();

	static void FlushFrameBuffer();
	static void Terminate();
	static bool GetIsOpenGLInit() { return OpenGlActive; }
private:

	static bool OpenGlActive;
	
	static void InitOpenGL(int VersionMinor, int VersionMajor);

	
};

