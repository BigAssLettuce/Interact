#pragma once
#include <vector>
#include "Entity.h"

#include "../../Modules/Render/3D/Render3D.h"



static class ECS
{


	static double Time;
	static double DeltaTime;

public:
	static void Init();
	static void UpdateEntities();
	static void RenderEntities();

};


