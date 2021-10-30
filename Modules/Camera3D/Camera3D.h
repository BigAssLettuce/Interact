#pragma once

#include "../../Core/glm.h"
#include <vector>
#include "../../Core/RenderAPI/Buffers/Uniform/UniformBuffer.h"
#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"

class Camera3D
{
#define CAMERA3D_UNIFORM_NAME "Camera3DData"
public: 
	
	

private:
	
	static UniformBuffer* UBO;
	const unsigned int UBOsize = sizeof(glm::mat4) * 3;
public:



	glm::vec3 WS_Pos = glm::vec3(0, 0, 0);
	glm::quat Rotation = glm::quat();
	glm::mat4 ProjMat = glm::mat4(1.0f);
	glm::mat4 ViewMat = glm::mat4(1.0f);


	Camera3D();
	~Camera3D();
	void ComputeTRSViewMatrix();
	void SetProjMatrix(glm::mat4 _ProjMat) { ProjMat = _ProjMat; }
	void GenPersProjMat(float FOV,float Nearclip, float Farclip);
	void Use();


	
};


