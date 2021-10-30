#include "LightManager.h"

#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"
LightManager* LightManager::INSTANCE;
LightManager::LightManager()
{
	UBO_Binding_Manager* ubmanager = UBO_Binding_Manager::GetInstance();
	ubmanager->RegisterBindingPoint("Lights");
	ubmanager->GetBindingPoint("Lights");
}

LightManager* LightManager::GetInstance()
{
	if (!INSTANCE) INSTANCE = new LightManager();
	return INSTANCE;
}
