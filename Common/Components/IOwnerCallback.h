#pragma once
#include "../Entity.h"
class IOwnerCallback {
public:
	Entity* owner;
	IOwnerCallback(Entity* _owner) { owner = _owner; }
};