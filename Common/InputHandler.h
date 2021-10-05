#pragma once
#include "../Core/include.h"
#include "../Core/Window.h"
#include <map>
enum MouseInputs {
	MOUSE1 = GLFW_MOUSE_BUTTON_1
};
static class InputHandler {
	InputHandler() {

		
	}
	map<Window*, InputHandleInstance> InputHandlers;
	//input handler per monitor = general + perkey
};
class InputHandleInstance {

};