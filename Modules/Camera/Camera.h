#pragma once

#include "../../Core/glm.h"
#include <vector>
#include "../../Core/RenderAPI/Buffers/Uniform/UniformBuffer.h"
#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"
class ECS;
class Camera
{
#define CAMERA3D_UNIFORM_NAME "Camera3DData"
	friend ECS;
	
	

private:
	
	static vector<Camera*> CAMERAS;
	static UniformBuffer* UBO;
	const unsigned int UBOsize = sizeof(glm::mat4) * 3 +sizeof(float)*2;


	
	float zNear = 0.1;
	float zFar = 15;
public:

	glm::mat4 ProjMat = glm::mat4(1.0f);
	glm::mat4 ViewMat = glm::mat4(1.0f);

	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::quat Rotation = glm::quat();
	


	Camera();
	~Camera();
	void ComputeTRSViewMatrix();
	void SetProjMatrix(glm::mat4 _ProjMat) { ProjMat = _ProjMat; }
	void GenPersProjMat(float FOV,float Nearclip, float Farclip);
	void Use();

	bool IsInCameraFrustum(glm::vec3 Point) {
		return true;
	}


	
};


