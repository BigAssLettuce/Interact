#pragma once

#include "../Buffer.h"
#include <vector>


class Debugger;
#define IndexElement unsigned short
class UniformBuffer :public Buffer{

	friend Debugger;




	//const UBO_Usage BufferUsage;
public:
	
	UniformBuffer(int _BufferSize,BufferUsage _usage);
	UniformBuffer(){}

	//void InsertData(int offset, int DataSize, const void* dataPointer);

	//void InsertData(int offset, UBOData datas..)
	void BindBufferBindingPoint(int BindingPoint);
};

