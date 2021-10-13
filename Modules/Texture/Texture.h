#pragma once
#include "../../Core/include.h"
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
	
	static vector<Texture*> TEXTURES;
public:
	Texture();
	static void DrawDebugMenu(bool* open) {
		ImGui::Begin("Textures", open);
		int i = 0;
		int texturecount = TEXTURES.size();
		//float size[texturecount];
		for (Texture* tex : TEXTURES) {
			if (ImGui::TreeNode(to_string(tex->TextureID).c_str())) {

				ImVec2 Winsize = ImGui::GetWindowSize();
				int border = 20;
				static float size = 25;
				string name = "Size" + string("##") + to_string(i);
				i++;
				ImGui::SliderFloat(name.c_str(), &size, 1, std::min(Winsize.x, Winsize.y));



				float aspectratio = tex->Size.x/ tex->Size.y;

				ImTextureID imtex = ImTextureID(tex->TextureID);
				//ImVec2(size - border, (size - border) * aspectratio)
				
				ImGui::Image(imtex, ImVec2(std::max(1.0f, size * aspectratio - border),std::max(1.0f, size   - border)), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));

				ImGui::TreePop();
			}
			
		}
		ImGui::End();
	}
	ivec2 Size = ivec2(1, 1);
	int FileSizeInBytes = 0;
	int ChannelsInFile = 1;
	
	void LoadTexture2D(string File);
	void Bind(int slot);

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

