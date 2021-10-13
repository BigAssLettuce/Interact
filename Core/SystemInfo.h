#pragma once
#include "include.h"
static class GlobalInfo {
	GlobalInfo() {
		glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &GPU_MAX_MEMORY);
	}
private:
	static GLint GPU_MAX_MEMORY;

};