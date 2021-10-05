#include "EntityManager.h"

std::vector<Entity*> EntityManager::ENTITIES = std::vector<Entity*>();
std::vector<RenderComponent*> EntityManager::RENDERERS = std::vector<RenderComponent*>();

void EntityManager::UpdateEntities(){ for (Entity* entity : ENTITIES) entity->Update();}
void EntityManager::RegisterEntity(Entity* _entity) { ENTITIES.push_back(_entity); }

void EntityManager::RenderEntities() { 
	for (RenderComponent* renderer : RENDERERS) 
	{
		renderer->SetupForRender();
		renderer->owner->PreRender();
		renderer->Render();
		renderer->owner->PostRender();
	} 
}
void EntityManager::RegisterRenderer(RenderComponent* _renderer) { RENDERERS.push_back(_renderer); }
