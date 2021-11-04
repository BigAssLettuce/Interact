#include "Buffer.h"
vector<Buffer*> Buffer::BUFFERS = vector<Buffer*>();
//BufferTypes Buffer::BufferType;
Buffer::Buffer(int _MemorySize, BufferUsage _usage,BufferTypes type) : BufferSize(_MemorySize)
{
	
	BufferType = type;
	glCreateBuffers(1, &BufferID);
	glBindBuffer(type, BufferID);
	glBufferData(type, _MemorySize, NULL, _usage);
	glBindBuffer(type, 0);
	Console::Log("Buffer ID:" + to_string(BufferID) + " Type:" + to_string(BufferType));

	BUFFERS.push_back(this);
}

void Buffer::Bind()
{
	glBindBuffer(BufferType, BufferID);
}

void Buffer::UnBind()
{
	glBindBuffer(BufferType, 0);
}

void Buffer::InsertData(int offset, int DataSize, const void* dataPointer)
{
	glBindBuffer(BufferType, BufferID);
	//int sizetest;
	//glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &sizetest);
	//Console::Log("Buffer Size is " + to_string(sizetest));
	glBufferSubData(BufferType, offset, DataSize, dataPointer);
	if (offset + DataSize > BufferSize) Console::Warning("Buffer (" + to_string(BufferID) + ") Inserted memory exceeds buffer size. use Resize();");
	glBindBuffer(BufferType, 0);
}
void Buffer::ReInitialize(int _size, BufferUsage _usage)
{
	this->Bind();
	glBufferData(BufferType, _size, NULL, _usage);
	this->UnBind();
}