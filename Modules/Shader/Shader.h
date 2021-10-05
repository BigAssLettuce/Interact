#pragma once
#include "../../Core/include.h"
#ifdef MODULE_CAMERA
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#endif
enum ShaderTypes {
	VERTEX,
	FRAGMENT,
	GEOMETRY
};
class Shader
{

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

public:
	const GLint shaderProgramID = glCreateProgram();
	Shader();
	~Shader();
	bool LoadShader(ShaderTypes types[], string files[]);
	bool LoadBasicShader(string vertex, string fragment);
	void Use();
	
};
