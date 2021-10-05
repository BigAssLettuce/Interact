#include "RenderComponent.h"
#include "../EntityManager.h"

RenderComponent::RenderComponent(Entity* _owner, Transform* transform) : IOwnerCallback(_owner)
{

	ownerTransform = transform;

	
	EntityManager::RegisterRenderer(this);
}

void RenderComponent::SetupForRender()
{
	ownerTransform->ComputeMatrix();
	ownerTransform->UpdateBuffer();


	MESH->Use();
	SHADER->Use();
	BindTextures();
}
void RenderComponent::Render()
{
	if (!cullmode) glDisable(GL_CULL_FACE);
	else {
		glEnable(GL_CULL_FACE);
		glCullFace(cullmode);
	}

	glDrawElements(drawMode,MESH->GetTriangleCount(), MESH_ELEMENTTYPE,nullptr);
	//Mesh::CleanUp();


}

void RenderComponent::BindTextures()
{
	int id = 0;
	for (Texture* tex : TEXTURES) {
		tex->Bind(id);
		id++;
	}
}