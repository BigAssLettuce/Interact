#include "ECS.h"
#include "../Camera/Camera.h"


void ECS::UpdateEntities(){ for (Entity* entity : Entity::ENTITIES) entity->Update();}

#include "../../Core/Debug/Gizmos/Gizmos.h"
#include "../Light/LightManager.h"
void ECS::RenderEntities() { 
	int i = 0;
	LightManager::GetInstance()->UploadLights();
	for (Camera* camera : Camera::CAMERAS) {
		camera->Use();

		for (Render3D* renderer : Render3D::RENDERERS)
		{

			bool RenderQ = renderer->SetupForRender();
			if (RenderQ) {
				Entity* owner = renderer->owner;
				owner->PreRender();
				renderer->Render();
				owner->PostRender();
			}
			i++;

		}
		if (Gizmos::GizmosEnabled) Gizmos::GetInstance()->Draw();
	}
	
}
double ECS::Time;
#include <chrono>
void ECS::Init()
{
	Time = glfwGetTime();
}

