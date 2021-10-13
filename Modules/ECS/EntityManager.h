#pragma once
#include <vector>
#include "Entity.h"

#include "../../Modules/Render/3D/Render3D.h"



static class EntityManager
{
	static std::vector<Entity*> ENTITIES;
	static std::vector<Render3D*> RENDERERS;


public:
	static void UpdateEntities();
	static void RegisterEntity(Entity* _entity);

	static void RenderEntities();
	static void RegisterRenderer(Render3D* _renderer);
};


