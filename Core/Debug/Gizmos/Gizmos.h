#pragma once
#include "../../glm.h"

#include <string>
#include "../../Shader/Shader.h"
#include "../Colors.h"

#include "../../RenderAPI/Buffers/VertexBuffer/VertexBuffer.h"
class Debugger;
class ECS;
static class Gizmos
{
	friend Debugger;
	friend ECS;

	static Gizmos* INSTANCE;
	Gizmos();

#pragma region LineStuff
	VertexBuffer* LineArrayBuffer;
	GLuint LineArrayBufferLayout;

	Shader* LineGizmoShader;

	string LineGizmoShaderVS = "#version 430 core\n"
		"layout (location = 0) in vec3 Vpos;\n"
		"uniform Camera3DData {mat4 ViewMat;mat4 ProjMat;mat4 ViewProjMat;vec3 Position; float zNear;float zFar;}; \n"
		"void main(){gl_Position =ViewProjMat*vec4(Vpos,1);}\n";

	string LineGizmoShaderFS = "#version 430 core\n"
		"out vec4 out_color;\n"
		"uniform vec4 GizmoColor = vec4(1,1,1,1);"
		"void main() {out_color = vec4(1,1,1,1);}\n";

#pragma endregion

	struct DrawCubeCmd {
		glm::vec3 PosData;
		glm::vec3 SizeData;
	};
	vector<DrawCubeCmd> DrawCubeCmds = vector<DrawCubeCmd>();
#pragma region CubeStuff
	VertexBuffer* CubeArrayBuffer;
	GLuint CubeArrayBufferLayout;
	GLuint CubeElementBuffer;

	Shader* CubeGizmoShader;
	GLint CubePosLoc = -1;
	GLint CubeSizeLoc = -1;
	string CubeGizmoShaderVS = "#version 430 core\n"
		"layout (location = 0) in vec3 Vpos;\n"
		"uniform vec3 Pos;"
		"uniform vec3 Size;"
		"uniform Camera3DData {mat4 ViewMat;mat4 ProjMat;mat4 ViewProjMat;vec3 Position; float zNear;float zFar;}; \n"
		"void main(){gl_Position =ViewProjMat*vec4(Vpos*(Size/2)+Pos,1);}\n";

	string CubeGizmoShaderFS = "#version 430 core\n"
		"out vec4 out_color;\n"
		"uniform vec4 GizmoColor = vec4(1,1,1,1);"
		"void main() {out_color = vec4(1,1,1,1);}\n";
#pragma endregion


	void Draw();
	void DrawWireCube(glm::vec3 Pos, glm::vec3 Size);
public:
	static bool GizmosEnabled;
	static Gizmos* GetInstance();
	void AddLine(glm::vec3 begin, glm::vec3 end, COLORS color = COLORS::WHITE);

	void AddWireCube(glm::vec3 Pos, glm::vec3 Size);
	


};

