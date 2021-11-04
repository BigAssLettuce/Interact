
#include "Render3D.h"



#include"../../../Core/Debug/Gizmos/Gizmos.h"

vector<Render3D*> Render3D::RENDERERS = vector<Render3D*>();
Render3D::Render3D(Entity* _owner, Transform3D* transform)
{

	_transform = transform;

	owner = _owner;
	RENDERERS.push_back(this);

}

bool Render3D::SetupForRender()
{
	_transform->ComputeMatrix();
	_transform->Use();

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
	//MESH->CleanUp();
	Mesh3DAABB bounds = MESH->BOUNDS;
	Gizmos::GetInstance()->AddWireCube(_transform->Position + bounds.Center, bounds.Size);
	


}

void Render3D::BindTextures()
{
	int id = 0;
	for (Texture2D* tex : TEXTURES) {
		tex->Bind(id);
		id++;
	}
}