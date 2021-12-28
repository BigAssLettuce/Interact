#pragma once
#include "Shader.h"
class ShaderInstance
{
	Shader* baseShader = nullptr;

	ShaderInstance(Shader* base);

	void Use();

	void Define(std::string def, std::string parameter);
	void Undefine(std::string def);

};

