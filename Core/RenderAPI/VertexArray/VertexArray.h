#pragma once
#include "../RenderAPI.h"
#include "../Buffers/VertexBuffer/VertexBuffer.h"
#include "../Buffers/ElementBuffer/ElementBuffer.h"

enum class VertexAttributeType {
	FLOAT = GL_FLOAT
};
class VertexArray
{
	GLuint CreateArray() { GLuint value; glCreateVertexArrays(1, &value); return value; }
	const GLuint ArrayID = CreateArray();

	VertexBuffer* VBO;
	ElementBuffer* EBO;
public:
	VertexArray();
	void Bind();
	static void UnBind();
	void BindVBO(VertexBuffer* _VBO);
	void BindEBO(ElementBuffer* _EBO);
	void AssignVertexAttribute(int index,int elementCount, VertexAttributeType type,bool Normalize,int Strife,const void* Pointer);
	void EnableVertexAttribute(int index);
	void DisableVertexAttribute(int index);


};

