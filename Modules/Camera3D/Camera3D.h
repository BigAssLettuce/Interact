#pragma once
#include "../../Core/include.h"
#include "../../Core/Application.h"
#include <vector>
using namespace glm;
class Camera3D
{
public: 
	//DONT TOUCH
	static GLuint CameraDataBufferID;
	static constexpr const char* CameraDataUniform = "CameraData";
	static const int CameraDataBufferBindingPoint = 1;
	//DONT TOUCH
	/*
	CameraData{
	mat4 View;
	mat4 Proj;
	mat4 ViewProj;
	}
	*/
private:
	

public:



	vec3 WS_Pos = vec3(0, 0, 0);
	quat Rotation = quat();
	mat4 ProjMat = mat4(1.0f);
	mat4 ViewMat = mat4(1.0f);


	Camera3D();
	~Camera3D();
	void ComputeViewMatrix();
	void SetProjMatrix(mat4 _ProjMat) { ProjMat = _ProjMat; }
	void GenPersProjMat(float FOV,float Nearclip, float Farclip);
	void UpdateBuffer();


	
};


