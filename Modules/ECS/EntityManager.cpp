#include "EntityManager.h"

std::vector<Entity*> EntityManager::ENTITIES = std::vector<Entity*>();
std::vector<Render3D*> EntityManager::RENDERERS = std::vector<Render3D*>();

void EntityManager::UpdateEntities(){ for (Entity* entity : ENTITIES) entity->Update();}
void EntityManager::RegisterEntity(Entity* _entity) { ENTITIES.push_back(_entity); }

void EntityManager::RenderEntities() { 
	for (Render3D* renderer : RENDERERS)
	{
		renderer->SetupForRender();
		renderer->owner->PreRender();
		renderer->Render();
		renderer->owner->PostRender();
	} 
}
void EntityManager::RegisterRenderer(Render3D* _renderer) { RENDERERS.push_back(_renderer); }
