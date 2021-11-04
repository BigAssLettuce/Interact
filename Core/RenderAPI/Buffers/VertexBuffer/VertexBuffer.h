#pragma once
#include "../Buffer.h"
class Debugger;

class VertexBuffer : public Buffer
{
	friend Debugger;

public:
	VertexBuffer(int _BufferSize, BufferUsage _usage);
};

