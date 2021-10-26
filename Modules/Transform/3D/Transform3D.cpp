#include "Transform3D.h"
#include "../../../Core/Registry.h"
GLuint Transform3D::TransformDataBufferID = -1;
int Transform3D::TransformDataBufferBindingPoint = -1;
Transform3D::Transform3D()
{
	int BufferSize =
		sizeof(vec3) //pos
		+ sizeof(quat) //quat
		+ sizeof(vec3) //euler
		+ sizeof(vec3)//scale
		+ sizeof(mat4); //model matrix

	//add a check if opengl context exists
	if (TransformDataBufferBindingPoint == -1) TransformDataBufferBindingPoint=Registry::RegisterUniform(TransformDataUniform);
	glCreateBuffers(1, &TransformDataBufferID);
	Console::Log("Transform Uniform Buffer ID " + std::to_string(TransformDataBufferID));
	glBindBuffer(GL_UNIFORM_BUFFER, TransformDataBufferID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 3 + sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, TransformDataBufferBindingPoint, TransformDataBufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);



}


void Transform3D::ComputeMatrix()
{
	mat4 PosMat = translate(mat4(1.0f), Position);
	mat4 RotMat = toMat4(Rotation);
	mat4 ScaleMat = scale(mat4(1.0f), Scale);
	ModelMatrix = PosMat * ScaleMat* RotMat;
}


void Transform3D::UpdateBuffer()
{
	float testfloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	int index = 0;
	glBindBuffer(GL_UNIFORM_BUFFER, TransformDataBufferID);

	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(mat4), &ModelMatrix[0][0]);
	index += sizeof(mat4);

	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(float), &testfloat);
	index += sizeof(float);

	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec3), &Position[0]);//pos
	index += sizeof(vec3);

	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec4), &Rotation.x);//quat
	index += sizeof(vec4);

	vec3 euler = eulerAngles(Rotation);
	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec3), &euler);//euler
	index += sizeof(vec3);

	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec3), &Scale);
	index += sizeof(vec3);


	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}
