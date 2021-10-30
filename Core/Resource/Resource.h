#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Debug/Console.h"
static class Resource {
public:
	static bool ReadTextFile(std::string File,std::string* output) {
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