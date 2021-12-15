#pragma once
#include "../../Core/Shader/Shader.h"
#include "../../Dependencies/glm-master/glm/glm.hpp"
#include <vector>
#include "../../Core/Texture/Texture.h"
class Material
{
	Shader* BaseShader;

	
	map<string, int> Uniforms = map<string, int>();

	map<int, float> Floats =		map<int, float>();
	map<int, glm::vec2> Vec2s =		map<int, glm::vec2>();
	map<int, glm::vec3> Vec3s =		map<int, glm::vec3>();
	map<int, glm::vec4> Vec4s =		map<int, glm::vec4>();
	map<int, Texture2D*> Textures = map<int, Texture2D*>();
};

