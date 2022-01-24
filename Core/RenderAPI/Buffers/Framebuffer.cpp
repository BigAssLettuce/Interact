#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
	if (!Application::GetIsOpenGLInit()) {
		Console::Error("Attempting to Create Framebuffer before OpenGL is init");
		return;
	}

	glGenTextures(1, &ID);

}
