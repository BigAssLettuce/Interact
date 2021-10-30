#pragma once
#include "../../../Core/RenderAPI/RenderAPI.h"
#include "../../../Core/Debug/Console.h"
enum BufferUsage {
	STREAM_DRAW = GL_STREAM_DRAW,
	STREAM_READ = GL_STREAM_READ, 
	STREAM_COPY = GL_STREAM_COPY,
	STATIC_DRAW = GL_STATIC_DRAW, 
	STATIC_READ = GL_STATIC_READ, 
	STATIC_COPY = GL_STATIC_COPY,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	DYNAMIC_READ = GL_DYNAMIC_READ,
	DYNAMIC_COPY = GL_DYNAMIC_COPY
};

enum BufferTypes {
	UNIFORM = GL_UNIFORM_BUFFER,
	ARRAY
};

class Debugger;
class Buffer
{
	friend Debugger;

protected:
	BufferTypes BufferType;
	unsigned int BufferSize;
	static vector<Buffer*> BUFFERS;
	GLuint BufferID = -1;
	
	Buffer(int _MemorySize, BufferUsage _usage, BufferTypes type);
public:
	BufferTypes GetType() { return BufferType; }
	unsigned int GetSize() { return BufferSize; }
	GLuint GetID() { return BufferID; }


	
};

