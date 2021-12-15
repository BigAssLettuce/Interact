#pragma once
#include "MainWindow.h"
#include "../Window/Window.h"
#if defined(_WIN32)
#include <stdlib.h>
#include <windows.h>
#elif defined(__linux__)
#include <sstream>
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
#include <iostream>
class Debugger;
static class Application
{
	friend Debugger;
public:
	
	static const char* GetExecutablePath() {

		char buffer[MAX_PATH];
		::GetModuleFileNameA(NULL,buffer, MAX_PATH);
		return buffer;
	}
	static const char* GetExecutableDir() {
		const char* buffer = GetExecutablePath();

		std::string sbuffer = std::string(buffer);
		
		return sbuffer.substr(0,sbuffer.find_last_of('\\')).c_str();
	}
	
	static void init(WindowSettings ws);
	static void ChangeWindowSettings(WindowSettings ws);
	static bool ShouldClose();

	static Window MainWindow;
	static void PreRender();

	static void PollEvents();

	static void Terminate();
	static bool GetIsOpenGLInit() { return OpenGlActive; }
private:

	static bool OpenGlActive;
	
	static void InitOpenGL(int VersionMinor, int VersionMajor);

	
};

