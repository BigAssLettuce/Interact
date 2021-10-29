#pragma once
#include "../../Core/include.h"
#include "../../Core/Registry.h"
#ifdef MODULE_CAMERA
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#endif
enum ShaderTypes {
	VERTEX,
	FRAGMENT,
	GEOMETRY
};

struct ShaderPart {
	ShaderTypes Type;
	string Content;
};
class Debugger;
class Shader
{
	friend Debugger;
	void CheckForUniformBuffers() {
		#ifdef MODULE_CAMERA
		int CameraDataIndex = glGetUniformBlockIndex(shaderProgramID, CameraComponent::CameraDataUniform);
		if (CameraDataIndex != -1) {
			Debug::Log("ShaderProgram " + to_string(shaderProgramID) + " contains uniform "+ CameraComponent::CameraDataUniform + " at "+to_string(CameraDataIndex));
		}

		int TransformDataIndex = glGetUniformBlockIndex(shaderProgramID, TransformComponent::TransformDataUniform);
		if (TransformDataIndex != -1) {
			Debug::Log("ShaderProgram " + to_string(shaderProgramID) + " contains uniform " + TransformComponent::TransformDataUniform + " at " + to_string(TransformDataIndex));
		}
		#endif
	}

	string ParseUniformBuffers(string source) {
		string returnstring = source;
		int pos = 0;
		for (string UBOname : Registry::GetUniformBuffers()) {
			size_t loc = returnstring.find("uniform " + UBOname);
			if (loc != -1) {
				//Debug::Log(to_string(static_cast<int>(loc)));
				returnstring.insert(static_cast<int>(loc), "layout (std140,binding = " + to_string(pos) + ")");
				Console::Log("Added uniform buffer at " + to_string(pos));
			}
			pos++;
		}
		//Debug::Log(returnstring);
		return returnstring;
	}
	vector<ShaderPart> ShaderParts = vector<ShaderPart>();
	static vector<Shader*> SHADERS;
public:
	string Name = "No Name";
	const GLint shaderProgramID = glCreateProgram();
	Shader();
	~Shader();
	bool LoadShader(ShaderTypes types[], string files[]);
	bool LoadBasicShader(string vertex, string fragment);
	void Use();
	
};
