#include "EntityManager.h"

std::vector<Entity*> EntityManager::ENTITIES = std::vector<Entity*>();
std::vector<ObjectRender*> EntityManager::RENDERERS = std::vector<ObjectRender*>();

void EntityManager::UpdateEntities(){ for (Entity* entity : ENTITIES) entity->Update();}
void EntityManager::RegisterEntity(Entity* _entity) { ENTITIES.push_back(_entity); }

void EntityManager::RenderEntities() { 
	for (ObjectRender* renderer : RENDERERS)
	{
		renderer->SetupForRender();
		renderer->owner->PreRender();
		renderer->Render();
		renderer->owner->PostRender();
	} 
}
void EntityManager::RegisterRenderer(ObjectRender* _renderer) { RENDERERS.push_back(_renderer); }
