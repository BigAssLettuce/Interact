#pragma once
#include "../../Core/include.h"
#include "IOwnerCallback.h"
#include "../../Modules/Transform/Transform.h"
#include "../../Modules/Shader/Shader.h"
#include "../../Modules/Mesh/Mesh.h"
#include "../../Modules/Texture/Texture.h"
#include <vector>
enum CULLMODE {
	OFF = 0,
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	FRONTANDBACK = GL_FRONT_AND_BACK
};
class RenderComponent : public IOwnerCallback
{
	GLuint VertexArrayID;
	GLuint VertexBufferID;
	Transform* ownerTransform;
	
	void BindTextures();
public:
	CULLMODE cullmode = BACK;
	GLenum drawMode = GL_TRIANGLES;
	Mesh* MESH;
	Shader* SHADER;
	vector<Texture*> TEXTURES = vector<Texture*>(); //maybe change to dictionary
	RenderComponent(Entity* _owner, Transform* transform);
	void SetupForRender();
	void Render();
};
