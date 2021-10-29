#pragma once
#include "../../Core/include.h"
#include "../../Core/Debug/Debugger.h"
enum class TextureType{
	TEXTURE2D,
	CUBEMAP
};
enum MinMethods {
	MIN_NEAREST = GL_NEAREST,
	MIN_LINEAR = GL_LINEAR,
	MIN_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	MIN_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	MIN_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
	MIN_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR
};
enum MagMethods {
	MAG_NEAREST = GL_NEAREST,
	MAG_LINEAR = GL_LINEAR
};
enum WrapMethods {
	WRAP_REPEAT = GL_REPEAT,
	WRAP_MIRROR_REPEAT = GL_MIRRORED_REPEAT,
	WRAP_CLAMP = GL_CLAMP_TO_EDGE
};
class Texture2D
{
	friend Debugger;
private:
	GLuint GenTexture() {
		GLuint id;
		glGenTextures(1, &id);
		//Console::Log("gen texture: " + to_string(id));
		
		return id;
	}
	GLuint TextureID = GenTexture();
	
	static vector<Texture2D*> TEXTURES;
public:
	Texture2D();


	string File;
	ivec2 Size = ivec2(1, 1);
	int FileSizeInBytes = 0;
	int ChannelsInFile = 1;
	
	void LoadTexture2D(string File);
	void Bind(int slot);
	void GetData();
	void SetMinMethod(MinMethods method) { 
		glBindTexture(GL_TEXTURE_2D,TextureID); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, method); 
	}
	void SetMagMethod(MagMethods method) { 
		glBindTexture(GL_TEXTURE_2D,TextureID); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, method); 
	}
	void SetWrapMethod(WrapMethods method) { 
	glBindTexture(GL_TEXTURE_2D,TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, method);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, method);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, method);
	}


};

