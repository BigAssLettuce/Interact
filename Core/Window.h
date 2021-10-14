#pragma once
#include "include.h"
#include <vector>
#include <map>
enum WindowModes {
	WINDOWED,
	BORDERLESS,
	FULLSCREEN
};
struct WindowSettings {
	//WindowSettings();

	vec2 Size = vec2(600, 400);
	const char* Title = "Default Title";
	WindowModes WindowMode = WINDOWED;

	bool Resizeable = true;
};



static class Window
{
private:
	static WindowSettings windowsettings;

public:
	
	static GLFWwindow* GlWindowPointer;
	
	static void init(WindowSettings ws); //DESTROYS EXISTING WINDOW
	static bool ShouldClose();
	static void FlushFramebuffer();
	static WindowSettings getWindowSettings();





};

