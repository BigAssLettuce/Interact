
#include "Render3D.h"

#include "../../ECS/EntityManager.h"


Render3D::Render3D(Entity* _owner, Transform3D* transform)
{

	_transform = transform;

	owner = _owner;
	EntityManager::RegisterRenderer(this);
}

bool Render3D::SetupForRender()
{
	_transform->ComputeMatrix();
	_transform->UpdateBuffer();

	if (!MESH)return false;
	if (!SHADER) return false;
	MESH->Use();
	SHADER->Use();
	if (TEXTURES.size()!=0)BindTextures();
	return true;
	
}
void Render3D::Render()
{
	if (!cullmode) glDisable(GL_CULL_FACE);
	else {
		glEnable(GL_CULL_FACE);
		glCullFace(cullmode);
	}

	glDrawElements(drawMode,MESH->GetTriangleCount(), MESH_ELEMENTTYPE,nullptr);

	


}

void Render3D::BindTextures()
{
	int id = 0;
	for (Texture2D* tex : TEXTURES) {
		tex->Bind(id);
		id++;
	}
}