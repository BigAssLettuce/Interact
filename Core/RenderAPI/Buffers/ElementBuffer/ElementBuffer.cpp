#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(int _MemorySize, BufferUsage _usage) : Buffer(_MemorySize,_usage,ELEMENT)
{
}
