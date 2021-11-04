#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "../../Dependencies/Imgui/imgui.h"
#include "../../Dependencies/Imgui/imgui_impl_glfw.h"
#include "../../Dependencies/Imgui/imgui_impl_opengl3.h"
#include "Colors.h"


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
		COLORS color;
	};
	static vector<Line> NewConsoleLog;
	static void AddToConsoleLog(string log, COLORS color);
	static void Log(string log, COLORS color = COLORS::WHITE);
	static void Warning(string warning);
	static void Error(string error);
	static void Critical(string critical);
	static bool ConsoleOpen;
	static bool AutoScroll;

	static void DrawImguiConsole();

};