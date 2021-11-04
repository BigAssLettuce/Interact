#pragma once
#include "../Buffer.h"
class Debugger;

class ArrayBuffer : public Buffer
{
	friend Debugger;

public:
	ArrayBuffer(int _BufferSize, BufferUsage _usage);
};

