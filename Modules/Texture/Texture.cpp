#include "Texture.h"
#include "../../Core/Debug/Console.h"
#include "../../Dependencies/std_image/stb_image.h"
std::vector<Texture2D*> Texture2D::TEXTURES = std::vector<Texture2D*>();


Texture2D::Texture2D()
{
	TEXTURES.push_back(this);
}
#include <iomanip>


void Texture2D::LoadTexture2D(std::string file)
{
	std::string fullpath = file;
	File = file;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* TexData = stbi_load(fullpath.c_str(), &Size.x, &Size.y, &ChannelsInFile, 4);
	if (TexData == NULL) {
		Console::Error("Error loading Texture File: " + file);
		return;
	}
	
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Size[0], Size[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, TexData);
	glGenerateMipmap(GL_TEXTURE_2D);

	int filesize = Size.x * ChannelsInFile + Size.y * ChannelsInFile;
	Console::Log("Loaded Texture " + file + " ID " + std::to_string(TextureID));
	stbi_image_free(TexData);
}

void Texture2D::Bind(int slot)
{
	GLenum BindSlot = GL_TEXTURE0;

	BindSlot += slot;
	glActiveTexture(BindSlot);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	//Debug::Log("texture Bindind " + to_string(TextureID) + " to " + to_string(BindSlot));
}

void Texture2D::GetData()
{
	
}



