#pragma once
#include "../../Core/include.h"
enum class TextureType{
	TEXTURE2D,
	CUBEMAP
};
class Texture
{
private:
	GLuint GenTexture() {
		GLuint id;
		glGenTextures(1, &id);
		Debug::Log("gen texture: " + to_string(id));
		return id;
	}
	GLuint TextureID = GenTexture();
	

public:
	ivec2 Size = ivec2(1, 1);
	int ChannelsInFile = 1;
	
	void LoadTexture2D(string File);

	void Bind(int slot);
};

