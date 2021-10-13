#pragma once
#include "../../../Core/include.h"
class Transform2D
{
public:
		static GLuint TransformDataBufferID;
	static constexpr const char* TransformDataUniform = "TransformData";
	static const int TransformDataBufferBindingPoint = 2;
	vec2 Position = vec2(0, 0);
	float Rotation = 0;
	vec2 Scale = vec2(1, 1);

	mat3 ModelMatrix = mat3(1.0f);

	void ComputeMatrix();
	void UpdateBuffer();
};

