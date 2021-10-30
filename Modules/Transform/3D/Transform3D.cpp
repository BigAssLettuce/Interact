#include "Transform3D.h"
//#include "../../../Core/Registry.h"

#include "../../../Core/RenderAPI/Buffers/Uniform/UniformBuffer.h"
#include "../../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"



UniformBuffer* Transform3D::uniformBufffer;



//UniformBuffer* UBO;
Transform3D::Transform3D()
{

	if (!uniformBufffer) {

		uniformBufffer = new UniformBuffer(UBOSize, DYNAMIC_DRAW);
		uniformBufffer->BindBufferBindingPoint(UBO_Binding_Manager::GetInstance()->RegisterBindingPoint(TRANSFORM3D_UNIFORM_NAME));

	}

}


void Transform3D::ComputeMatrix()
{
	glm::mat4 PosMat = glm::translate(glm::mat4(1.0f), Position);
	glm::mat4 RotMat = glm::toMat4(Rotation);
	glm::mat4 ScaleMat = glm::scale(glm::mat4(1.0f), Scale);
	ModelMatrix = PosMat * ScaleMat * RotMat;
}


void Transform3D::Use()
{

	int index2 = 0;
	uniformBufffer->InsertData(index2, sizeof(glm::mat4), &ModelMatrix[0][0]);
	index2 += sizeof(glm::mat4);
	uniformBufffer->InsertData(index2, sizeof(glm::vec3), &Position[0]);
	index2 += sizeof(glm::vec3);
	uniformBufffer->InsertData(index2, sizeof(glm::vec4), &Rotation[0]);
	index2 += sizeof(glm::vec4);
	glm::vec3 euler2 = eulerAngles(Rotation);
	uniformBufffer->InsertData(index2, sizeof(glm::vec3), &euler2[0]);
	index2 += sizeof(glm::vec3);
	uniformBufffer->InsertData(index2, sizeof(glm::vec3), &Scale[0]);
	index2 += sizeof(glm::vec3);

}
