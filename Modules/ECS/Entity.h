#pragma once

#include <vector>

class ECS;
class Debugger;
class Entity
{
	friend ECS;
	friend Debugger;
	static std::vector<Entity*> ENTITIES;


public:
	Entity();
	virtual void Update(){}
	virtual void PreRender(){}
	virtual void PostRender(){}
	virtual void DebugMenu(){}
};



