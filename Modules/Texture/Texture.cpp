#include "Texture.h"
#include "stb_image.h"



void Texture::LoadTexture2D(string file)
{
	string fullpath = file;
	
	stbi_set_flip_vertically_on_load(1);
	unsigned char* TexData = stbi_load(fullpath.c_str(), &Size.x, &Size.y, &ChannelsInFile, 4);

	if (TexData == NULL) {
		Debug::Log("Error loading Texture File: " + file + " at " + fullpath);
		return;
	}
	
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Size[0], Size[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, TexData);
	glGenerateMipmap(GL_TEXTURE_2D);

	int filesize = Size.x * ChannelsInFile + Size.y * ChannelsInFile;
	Debug::Log("Loaded Texture " + file + " ID " + to_string(TextureID) +" : " + ParseBytes(filesize));
	stbi_image_free(TexData);
}

void Texture::Bind(int slot)
{
	GLenum BindSlot = GL_TEXTURE0;

	BindSlot += slot;
	glActiveTexture(BindSlot);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	//Debug::Log("texture Bindind " + to_string(TextureID) + " to " + to_string(BindSlot));
}



