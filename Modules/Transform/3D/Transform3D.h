#pragma once
#include "../../../Core/RenderAPI/Buffers/Uniform/UniformBuffer.h"
#include "../../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"
#include "../../../Core/glm.h"
#include <vector>

class Transform3D
{
#define TRANSFORM3D_UNIFORM_NAME "Transform3DData"
private:
	static std::vector<Transform3D*> Transforms;
	static const int UBOSize = sizeof(glm::mat4) +sizeof(glm::vec4) + sizeof(glm::vec3)*3;
	static UniformBuffer* uniformBufffer;
public:
	Transform3D();
	//DONT TOUCH
	//const static int TransformDataBufferBindingPoint;

	//DONT TOUCH

	glm::vec3 Position = glm::vec3(0, 0, 0);
	glm::quat Rotation = glm::quat();
	glm::vec3 Scale = glm::vec3(1, 1, 1);
	
	glm::mat4 ModelMatrix = glm::mat4(1.0f);
	
	void ComputeMatrix();
	void Use();
};

