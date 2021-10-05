


#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

#include "glm/common.hpp"
#include "stb_image.h"
#include "Debug.h"
#include "Resource.h"
#include <vector>
#ifdef DEBUG


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif



#include <string>


#ifndef DEFAULTDEPTHFUNC
#define DEFAULTDEPTHFUNC GL_LESS
#endif // !DEFAULTDEPTHFUNC





using namespace glm;
using namespace std;

static string ParseBytes(int Bytes) {
	int Levels = 0;
	bool isBiggerThanNext = true;
	while (isBiggerThanNext) {
		if (Bytes >= 1024) {
			Levels++;
			Bytes /= 1024;
		}
		else isBiggerThanNext = false;
	}
	string Unit;
	switch (Levels)
	{
	case 0:
		Unit = "B";
		break;
	case 1:
		Unit = "KB";
		break;
	case 2:
		Unit = "MB";
		break;
	case 3:
		Unit = "GB";
		break;
	default:
		break;
	}
	return to_string(Bytes) + Unit;
}

static std::vector<std::string> ParseString(std::string input, char separator) {
	std::string Current = "";
	std::vector<std::string> Total = {};
	for (int i = 0; i < input.length(); i++) {
		char CurrentLetter = input[i];
		if (CurrentLetter != separator) {
			Current += CurrentLetter;
		}
		else if (Current.length() > 0) {
			Total.push_back(Current);
			Current = "";

		}
	}

	if (Current.length() > 0) Total.push_back(Current);
	return Total;
}

template < typename T>
static std::pair<bool, int > findInVector(const std::vector<T>& vecOfElements, const T& element)
{
	std::pair<bool, int > result;
	// Find given element in vector
	auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
	if (it != vecOfElements.end())
	{
		result.second = std::distance(vecOfElements.begin(), it);
		result.first = true;
	}
	else
	{
		result.first = false;
		result.second = -1;
	}
	return result;
}