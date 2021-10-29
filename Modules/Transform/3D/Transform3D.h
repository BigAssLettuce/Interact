#pragma once
#include "../../../Core/include.h"
class Transform3D
{
private:
	static vector<Transform3D*> Transforms;
public:
	Transform3D();
	//DONT TOUCH
	static GLuint TransformDataBufferID;
	static constexpr const char* TransformDataUniform = "Transform3DData";
	static int TransformDataBufferBindingPoint;
#ifdef IMGUI
	static void DrawDebug() {
		ImGui::Begin("Transform3D");
		for (int i = 0; i < Transforms.size(); i++) {

		}
		ImGui::End();
	}
#endif
	//DONT TOUCH

	vec3 Position = vec3(0, 0, 0);
	quat Rotation = quat();
	vec3 Scale = vec3(1, 1, 1);
	
	mat4 ModelMatrix = mat4(1.0f);
	
	void ComputeMatrix();
	void UpdateBuffer();
};

