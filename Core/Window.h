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
	static map<GLFWwindow*, Window*> WindowInstances;
public:
	GLFWwindow* GlWindowPointer;
	
	void init(WindowSettings ws); //DESTROYS EXISTING WINDOW
	bool ShouldClose();
	void FlushFramebuffer();
	WindowSettings getWindowSettings();

	static Window* GetWindowFromGLPointer(GLFWwindow* _pointer) { return WindowInstances.at(_pointer); }

private: //callbacks

	
public:
	struct WindowResizeEvent {
		Window* window;
		uvec2 size;
	};
	typedef void (*WindowReSizeCallback)(WindowResizeEvent);
	void WindowResizeRegister(WindowReSizeCallback _callback) {
		WindowResizeCallbacks.push_back(_callback);
	}
private:
	void DispatchWindowResizeEvent(uvec2 _size) {
		WindowResizeEvent event;
		event.window = this; event.size = _size;
		for (WindowReSizeCallback func : WindowResizeCallbacks)func(event);
	}
	static void GLWindowSizeCallback(GLFWwindow* window, int width, int height);
	vector<WindowReSizeCallback> WindowResizeCallbacks;
};

