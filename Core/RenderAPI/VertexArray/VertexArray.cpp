#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &ArrayID);
}

void VertexArray::Bind()
{
	glBindVertexArray(ArrayID);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::Use()
{
	//if (!EBO) {Console::Error("Vertex Array has no EBO Bound"); return;}
	if (!VBO) { Console::Error("Vertex Array has no VBo Bound"); assert("myass"); }

	Bind();
	//EBO->Bind();
	//VBO->Bind();
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
	Bind();
	glEnableVertexAttribArray(index);
	UnBind();
}

void VertexArray::DisableVertexAttribute(int index)
{
	Bind();
	glDisableVertexAttribArray(index);
	UnBind();
}



