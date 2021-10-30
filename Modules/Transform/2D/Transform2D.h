#pragma once

#include "../../../Core/glm.h"
class Transform2D
{
public:
		//static GLuint TransformDataBufferID;
	//static constexpr const char* TransformDataUniform = "TransformData";
	//static const int TransformDataBufferBindingPoint = 2;
	glm::vec2 Position = glm::vec2(0, 0);
	float Rotation = 0;
	glm::vec2 Scale = glm::vec2(1, 1);

	glm::mat3 ModelMatrix = glm::mat3(1.0f);

	void ComputeMatrix();
	void UpdateBuffer();
};

