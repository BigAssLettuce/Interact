#pragma once

#include <string>
#include <iostream>

using namespace std;
static class Console {
private:
	string log = "LOG";
	string error = "ERROR";
	string warning = "WARNING";
	string critical = "CRITICAL";

	
public:
	static string ConsoleLog;
	static void AddToConsoleLog(string log);
	static void Log(string log);
	static void Error(string error);
	static void Warning(string warning);
	static void Critical(string critical);
	static bool ConsoleOpen;
	static bool AutoScroll;
	
	static void DrawImguiConsole();
};