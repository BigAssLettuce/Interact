#pragma once
#include "../Buffer.h"
class ElementBuffer : public Buffer
{
	ElementBuffer();
public:
	ElementBuffer(int _MemorySize, BufferUsage _usage);
};

