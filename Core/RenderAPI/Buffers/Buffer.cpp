#include "Buffer.h"
vector<Buffer*> Buffer::BUFFERS = vector<Buffer*>();
Buffer::Buffer(int _MemorySize, BufferUsage _usage,BufferTypes type) : BufferSize(_MemorySize),BufferType(type)
{
	

	glCreateBuffers(1, &BufferID);
	glBindBuffer(type, BufferID);
	glBufferData(type, _MemorySize, NULL, _usage);
	glBindBuffer(type, 0);
	Console::Log("Buffer ID:" + to_string(BufferID) + " Type:" + to_string(BufferType));

	BUFFERS.push_back(this);
}
