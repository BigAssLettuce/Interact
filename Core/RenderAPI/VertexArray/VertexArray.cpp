#include "VertexArray.h"

VertexArray::VertexArray()
{
}

void VertexArray::Bind()
{
	glBindVertexArray(ArrayID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::BindVBO(VertexBuffer* _VBO)
{
	glBindVertexArray(ArrayID);
	VBO = _VBO;
	VBO->Bind();
	glBindVertexArray(0);
}

void VertexArray::BindEBO(ElementBuffer* _EBO)
{
	glBindVertexArray(ArrayID);
	EBO = _EBO;
	EBO->Bind();
	glBindVertexArray(0);
}

void VertexArray::AssignVertexAttribute(int index, int elementCount, VertexAttributeType type, bool Normalize, int Strife, const void* Pointer)
{
	glBindVertexArray(ArrayID);
	glVertexAttribPointer(index, elementCount, (GLenum)type,Normalize, Strife, Pointer);
	glBindVertexArray(0);
}

void VertexArray::EnableVertexAttribute(int index)
{
	glEnableVertexAttribArray(index);
}

void VertexArray::DisableVertexAttribute(int index)
{
	glDisableVertexAttribArray(index);

}

