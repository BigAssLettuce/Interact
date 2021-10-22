#pragma once
#include "../../../Core/include.h"
#include "../../../Modules/Transform/3D//Transform3D.h"
#include "../../../Modules/Shader/Shader.h"
#include "../../../Modules/Mesh/Mesh.h"
#include "../../../Modules/Texture/Texture.h"
#include "../../../Modules/ECS/Entity.h"
#include <vector>
enum CULLMODE {
	OFF = 0,
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	FRONTANDBACK = GL_FRONT_AND_BACK
};
class Render3D 
{
	
	GLuint VertexArrayID;
	GLuint VertexBufferID;
	Transform3D* _transform;
	
	void BindTextures();
public:
	Entity* owner; //not absolutely necesary, only if object has owner

	CULLMODE cullmode = BACK;
	GLenum drawMode = GL_TRIANGLES;
	Mesh3D* MESH;
	Shader* SHADER;
	vector<Texture*> TEXTURES = vector<Texture*>(); //maybe change to dictionary
	Render3D(Entity* _owner, Transform3D* transform);
	bool SetupForRender();
	void Render();
};
