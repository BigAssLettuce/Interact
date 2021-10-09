#pragma once
#include "../../../Core/include.h"
class Transform3D
{
public:
	Transform3D();
	//DONT TOUCH
	static GLuint TransformDataBufferID;
	static constexpr const char* TransformDataUniform = "TransformData";
	static const int TransformDataBufferBindingPoint = 2;
	//DONT TOUCH

	vec3 Position = vec3(0, 0, 0);
	quat Rotation = quat();
	vec3 Scale = vec3(1, 1, 1);
	
	mat4 ModelMatrix = mat4(1.0f);
	
	void ComputeMatrix();
	void UpdateBuffer();
};

