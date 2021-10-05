#pragma once

#include <string>
#include <iostream>
using namespace std;
static class Debug {
private:
	string log = "LOG";
	string error = "ERROR";
	string warning = "WARNING";
	string critical = "CRITICAL";

	
public:
	static void Log(string log) {
		std::cout << "\033[0;37m[LOG]" << "\033[0m " << log  << std::endl;
	}
	static void Error(string error) {
		std::cout << "\033[0;31m[ERROR]" << "\033[0m " << error  << std::endl;
	}
	static void Warning(string warning) {
		std::cout << "\033[0;33m[WARNING]" << "\033[0m " << warning << std::endl;
	}
	static void Critical(string critical) {
		std::cout << "\033[41m[CRITICAL]" << "\033[0m " << critical  << std::endl;
	}
};