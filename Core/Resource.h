#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "Debug/Console.h"
using namespace std;
static class Resource {
public:
	static bool ReadTextFile(string File,string* output) {
		std::stringstream content;
		std::ifstream filestream(File);
		if (filestream.is_open()) {
			std::string line;
			while (std::getline(filestream, line)) {
				content << line << '\n';

			}
			filestream.close();
		}
		else {
			Console::Error("File not found " + File);
			return false;
		}
		*output = content.str();

		return true;
	}


};