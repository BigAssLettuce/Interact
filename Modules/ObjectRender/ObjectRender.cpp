
#include "ObjectRender.h"

#include "../ECS/EntityManager.h"


ObjectRender::ObjectRender(Entity* _owner, Transform3D* transform)
{

	ownerTransform = transform;

	owner = _owner;
	EntityManager::RegisterRenderer(this);
}

void ObjectRender::SetupForRender()
{
	ownerTransform->ComputeMatrix();
	ownerTransform->UpdateBuffer();


	MESH->Use();
	SHADER->Use();
	BindTextures();
}
void ObjectRender::Render()
{
	if (!cullmode) glDisable(GL_CULL_FACE);
	else {
		glEnable(GL_CULL_FACE);
		glCullFace(cullmode);
	}

	glDrawElements(drawMode,MESH->GetTriangleCount(), MESH_ELEMENTTYPE,nullptr);
	//Mesh::CleanUp();


}

void ObjectRender::BindTextures()
{
	int id = 0;
	for (Texture* tex : TEXTURES) {
		tex->Bind(id);
		id++;
	}
}