#pragma once
#include <vector>
#include "Entity.h"

#include "../../Modules/ObjectRender/ObjectRender.h"



static class EntityManager
{
	static std::vector<Entity*> ENTITIES;
	static std::vector<ObjectRender*> RENDERERS;


public:
	static void UpdateEntities();
	static void RegisterEntity(Entity* _entity);

	static void RenderEntities();
	static void RegisterRenderer(ObjectRender* _renderer);
};


