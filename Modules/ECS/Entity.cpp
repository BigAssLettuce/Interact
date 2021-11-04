#include "Entity.h"
std::vector<Entity*> Entity::ENTITIES = std::vector<Entity*>();
Entity::Entity()
{
	
	ENTITIES.push_back(this);
	
}
