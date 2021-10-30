#pragma once


struct Light {
	bool Enabled = true;
	float Intensity = 1;

};
struct PointLight : Light {

};
#include "../../Core/Core.h"
class LightManager
{
	LightManager();

	static LightManager* INSTANCE;
public:
	static LightManager* GetInstance();

};

