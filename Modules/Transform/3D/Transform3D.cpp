#include "Transform3D.h"

GLuint Transform3D::TransformDataBufferID = -1;
Transform3D::Transform3D()
{
	int BufferSize = 
		sizeof(vec3) //pos
		+ sizeof(quat) //quat
		+ sizeof(vec3) //euler
		+ sizeof(vec3)//scale
		+ sizeof(mat4); //model matrix

	if (TransformDataBufferID == -1) {
		glCreateBuffers(1, &TransformDataBufferID);
		glBindBuffer(GL_UNIFORM_BUFFER, TransformDataBufferID);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 3 + sizeof(float), NULL, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, TransformDataBufferBindingPoint, TransformDataBufferID);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		Debug::Log("Transform Uniform Buffer ID " + std::to_string(TransformDataBufferID));
	}
}


void Transform3D::ComputeMatrix()
{
	mat4 PosMat = translate(mat4(1.0f), Position);
	mat4 RotMat = toMat4(Rotation);
	mat4 ScaleMat = scale(mat4(1.0f), Scale);
	ModelMatrix = PosMat * RotMat * ScaleMat; 
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

	glBufferSubData(GL_UNIFORM_BUFFER, index, sizeof(vec3), &Position.x);//pos
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
