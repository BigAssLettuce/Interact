#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "../../Dependencies/Imgui/imgui.h"
#include "../../Dependencies/Imgui/imgui_impl_glfw.h"
#include "../../Dependencies/Imgui/imgui_impl_opengl3.h"

enum ConsoleColors {
	RED,
	ROSE,
	BLUE,
	CYAN,
	GREEN,
	WHITE,
	YELLOW,
	ORANGE
};
using namespace std;
static class Console {

	
private:
	string log = "LOG";
	string error = "ERROR";
	string warning = "WARNING";
	string critical = "CRITICAL";

	
public:
	static string ConsoleLog;
	struct Line {
		string lineContent;
		ConsoleColors color;
	};
	static vector<Line> NewConsoleLog;
	static void AddToConsoleLog(string log, ConsoleColors color);
	static void Log(string log,ConsoleColors color = ConsoleColors::WHITE);
	static void Warning(string warning);
	static void Error(string error);
	static void Critical(string critical);
	static bool ConsoleOpen;
	static bool AutoScroll;

	static void DrawImguiConsole();

};