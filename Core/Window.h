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



class Window
{
private:
	WindowSettings windowsettings;

public:
	
	GLFWwindow* GlWindowPointer;
	
	void init(WindowSettings ws); //DESTROYS EXISTING WINDOW
	bool ShouldClose();
	void FlushFramebuffer();
	WindowSettings getWindowSettings();





};

