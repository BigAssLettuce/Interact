#pragma once

#include "../../../Core/RenderAPI/RenderAPI.h"

#include "../../../Core/Shader/Shader.h"
#include "../../../Core/Texture/Texture.h"

#include "../../../Modules/Transform/3D/Transform3D.h"
#include "../../../Modules/Mesh/Mesh.h"
#include "../../../Modules/ECS/Entity.h"

#include <vector>
enum CULLMODE {
	OFF = 0,
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	FRONTANDBACK = GL_FRONT_AND_BACK
};
class ECS;
class Render3D 
{
	friend ECS;
	static vector<Render3D*> RENDERERS;
	GLuint VertexArrayID;
	GLuint VertexBufferID;
	Transform3D* _transform;
	
	void BindTextures();
public:
	Entity* owner; //not absolutely necesary, only if object has owner

	CULLMODE cullmode = BACK;
	GLenum drawMode = GL_TRIANGLES;
	OldMesh3D* MESH;
	Shader* SHADER;
	vector<Texture2D*> TEXTURES = vector<Texture2D*>(); //maybe change to dictionary
	Render3D(Entity* _owner, Transform3D* transform);
	bool SetupForRender();
	void Render();
};
