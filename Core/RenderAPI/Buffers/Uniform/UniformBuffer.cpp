#include "UniformBuffer.h"
#include "../../../../Core/Debug/Console.h"


UniformBuffer::UniformBuffer(int _BufferSize,BufferUsage _usage ) :Buffer(_BufferSize, _usage, UNIFORM)
{

}

void UniformBuffer::InsertData(int offset, int DataSize, const void* dataPointer) {
	glBindBuffer(GL_UNIFORM_BUFFER, BufferID);
	//int sizetest;
	//glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &sizetest);
	//Console::Log("Buffer Size is " + to_string(sizetest));
	glBufferSubData(GL_UNIFORM_BUFFER, offset, DataSize, dataPointer);
	if (offset + DataSize > BufferSize) Console::Warning("UBO (" + to_string(BufferID) + ") Inserted memory exceeds buffer size. use Resize();");
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::BindBufferBindingPoint(int BindingPoint)
{
	glBindBuffer(GL_UNIFORM_BUFFER, BufferID);
	glBindBufferBase(GL_UNIFORM_BUFFER, BindingPoint, BufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

