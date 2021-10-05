#include "Entity.h"
#include "EntityManager.h"
Entity::Entity()
{
	
	EntityManager::RegisterEntity(this);
	
}
