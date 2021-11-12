#pragma once

#include "../glm.h"
#include "../RenderAPI/RenderAPI.h"
#include <vector>
#include <map>
enum WindowModes {
	WINDOWED,
	BORDERLESS,
	FULLSCREEN
};
struct WindowSettings {
	//WindowSettings();

	glm::vec2 Size = glm::vec2(600, 400);
	const char* Title = "Default Title";
	WindowModes WindowMode = WINDOWED;

	bool Resizeable = true;
};



static class MainWindow
{
private:
	static WindowSettings windowsettings;

public:
	
	static GLFWwindow* GlWindowPointer;
	static void NewFrame(bool ClearColor = false);
	static void init(WindowSettings ws); //DESTROYS EXISTING WINDOW
	static bool ShouldClose();
	static void SetShouldClose(bool close);
	static void FlushFramebuffer();
	static WindowSettings getWindowSettings();





};

