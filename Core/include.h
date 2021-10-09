#pragma once


#define CONCAT2(a, b) a ## b
#define CONCAT(a, b) CONCAT2(a, b)
#define Q(x) #x
#define QUOTE(x) Q(x)


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"Gdi32.lib")
#pragma comment(lib,"Shell32.lib")
#ifndef INTERACT_DIR
#error "not defined INTERACT_DIR in Preprocessor Definitions. INTERACT_DIR = R"( InteractDirectoryHere )""
#endif
#define glew32sFile \\Dependencies\\GL\\GLEW\\lib\\Release\\x64\\glew32s.lib
#define glfw3File \\Dependencies\\GL\\GLFW\\lib-vc2019\\glfw3.lib

//#pragma comment(lib,QUOTE(CONCAT(INTERACT_DIR, glew32sFile)))//doesnt work
#pragma comment(lib,"C:\\Users\\camil\\Dropbox\\Interact\\Interact\\Dependencies\\GL\\GLEW\\lib\\Release\\x64\\glew32s.lib")

//#pragma comment(lib,QUOTE(CONCAT(INTERACT_DIR, glfw3File)))
//#pragma comment(lib,"C:\\Users\\camil\\Dropbox\\Interact\\Interact\\Dependencies\\GL\\GLFW\\lib-vc2019\\glfw3.lib")
#pragma comment(lib,R"(C:\Users\camil\Dropbox\Interact\Interact\Dependencies\GL\GLFW\lib-vc2019\glfw3.lib)")

#define GLEW_STATIC
#include "../Dependencies/GL/GLEW/include/GL/glew.h"
#include "../Dependencies/GL/GLFW/include/GLFW/glfw3.h"




#include "../Dependencies/glm-master/glm/glm.hpp"
#include "../Dependencies/glm-master/glm/gtc/matrix_transform.hpp"
#include "../Dependencies/glm-master/glm/gtc/quaternion.hpp"
#include "../Dependencies/glm-master/glm/gtx/quaternion.hpp"
#include "../Dependencies/glm-master/glm/gtx/string_cast.hpp"
#include "../Dependencies/glm-master/glm/common.hpp"
#include "../Dependencies/glm-master/glm/gtc/type_ptr.hpp"

#include "../Dependencies/std_image/stb_image.h"

#include "Debug.h"
#include "Resource.h"
#include <vector>
#ifdef DEBUG

#include "../Dependencies/Imgui/imgui.h"
#include "../Dependencies/Imgui/imgui_impl_glfw.h"
#include "../Dependencies/Imgui/imgui_impl_opengl3.h"
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

