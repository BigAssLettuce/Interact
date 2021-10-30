#pragma once
#include "../../Core/include.h"
#include "../../Core/Application.h"
#include <vector>
#include "../../Core/RenderAPI/Buffers/Uniform/UniformBuffer.h"
#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"
using namespace glm;
class Camera3D
{
#define CAMERA3D_UNIFORM_NAME "Camera3DData"
public: 
	
	

private:
	
	static UniformBuffer* UBO;
	const unsigned int UBOsize = sizeof(mat4) * 3;
public:



	vec3 WS_Pos = vec3(0, 0, 0);
	quat Rotation = quat();
	mat4 ProjMat = mat4(1.0f);
	mat4 ViewMat = mat4(1.0f);


	Camera3D();
	~Camera3D();
	void ComputeTRSViewMatrix();
	void SetProjMatrix(mat4 _ProjMat) { ProjMat = _ProjMat; }
	void GenPersProjMat(float FOV,float Nearclip, float Farclip);
	void Use();


	
};


