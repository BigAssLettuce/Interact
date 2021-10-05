#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "Debug.h"
using namespace std;
static class Resource {
public:
	static string ReadTextFile(string File) {
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
			Debug::Error("File not found " + File);
		}
		std::string stringcontent = content.str();

		return stringcontent;
	}
};