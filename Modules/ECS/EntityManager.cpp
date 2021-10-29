#include "EntityManager.h"

std::vector<Entity*> EntityManager::ENTITIES = std::vector<Entity*>();
std::vector<Render3D*> EntityManager::RENDERERS = std::vector<Render3D*>();

void EntityManager::UpdateEntities(){ for (Entity* entity : ENTITIES) entity->Update();}
void EntityManager::RegisterEntity(Entity* _entity) { ENTITIES.push_back(_entity); }

void EntityManager::RenderEntities() { 
	int i = 0;

	for (Render3D* renderer : RENDERERS)
	{

		bool Render = renderer->SetupForRender();
		
		renderer->owner->PreRender();
		if (Render)	renderer->Render();
		renderer->owner->PostRender();

		i++;
		
	} 
}
void EntityManager::RegisterRenderer(Render3D* _renderer) { RENDERERS.push_back(_renderer); }
