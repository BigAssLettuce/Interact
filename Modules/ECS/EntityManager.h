#pragma once
#include <vector>
#include "Entity.h"

#include "Components/RenderComponent.h"



static class EntityManager
{
	static std::vector<Entity*> ENTITIES;
	static std::vector<RenderComponent*> RENDERERS;


public:
	static void UpdateEntities();
	static void RegisterEntity(Entity* _entity);

	static void RenderEntities();
	static void RegisterRenderer(RenderComponent* _renderer);
};


