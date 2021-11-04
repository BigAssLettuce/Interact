#include "Gizmos.h"
#include "../../Resource/Resource.h"

Gizmos* Gizmos::INSTANCE;
bool Gizmos::GizmosEnabled = false;

Gizmos::Gizmos()
{
	
	//GizmoShader.LoadShader(vector<ShaderPart>{Vertex, Fragment});
	


#pragma region LineBuffer

	LineGizmoShader = new Shader();
	LineGizmoShader->LoadShader(vector<ShaderPart>{ShaderPart(VERTEX, LineGizmoShaderVS), ShaderPart(FRAGMENT, LineGizmoShaderFS)});
LineArrayBuffer = new ArrayBuffer(3 * sizeof(glm::vec3), BufferUsage::DYNAMIC_DRAW);

glGenVertexArrays(1, &LineArrayBufferLayout);
glBindVertexArray(LineArrayBufferLayout);
LineArrayBuffer->Bind();
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);//POS

glBindVertexArray(0);
#pragma endregion


#pragma region CubeBuffer

CubeGizmoShader = new Shader();



CubeGizmoShader->LoadShader(vector<ShaderPart>{ShaderPart(VERTEX, CubeGizmoShaderVS), ShaderPart(FRAGMENT, CubeGizmoShaderFS)});
glGenVertexArrays(1, &CubeArrayBufferLayout);
CubeArrayBuffer = new ArrayBuffer(8 * sizeof(glm::vec3), BufferUsage::STATIC_DRAW);
glm::vec3 CubeVerts[] = { glm::vec3(1,1,1),glm::vec3(1,1,-1),glm::vec3(-1,1,-1),glm::vec3(-1,1,1),
glm::vec3(1,-1,1),glm::vec3(1,-1,-1),glm::vec3(-1,-1,-1),glm::vec3(-1,-1,1) };
CubeArrayBuffer->InsertData(0, sizeof(CubeVerts), CubeVerts);
glCreateBuffers(1, &CubeElementBuffer);
unsigned int CubeLineElements[] = { 0,1,1,2,2,3,3,0,
						            4,5,5,6,6,7,7,4,
							        0,4,1,5,2,6,3,7 };
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeElementBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeLineElements), CubeLineElements, GL_STATIC_DRAW);



glBindVertexArray(CubeArrayBufferLayout);
CubeArrayBuffer->Bind();
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeElementBuffer);


glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);//POS
CubePosLoc = CubeGizmoShader->getUniformLocation("Pos");
Console::Log("Pos: " + to_string(CubePosLoc));
CubeSizeLoc = CubeGizmoShader->getUniformLocation("Size");
#pragma endregion

}

void Gizmos::Draw()
{
	for (DrawCubeCmd cmd : DrawCubeCmds) {
		DrawWireCube(cmd.PosData, cmd.SizeData);
	}
	DrawCubeCmds.clear();
}

void Gizmos::DrawWireCube(glm::vec3 Pos, glm::vec3 Size)
{
	CubeGizmoShader->Use();
	glBindVertexArray(CubeArrayBufferLayout);

	//CubeArrayBuffer->Bind();
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeElementBuffer);
	//glEnableVertexAttribArray(0);
	glUniform3fv(CubePosLoc, 1, &Pos[0]);
	glUniform3fv(CubeSizeLoc, 1, &Size[0]);

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	//glDisableVertexAttribArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Gizmos* Gizmos::GetInstance() { if (!INSTANCE) INSTANCE = new Gizmos(); return INSTANCE; }

void Gizmos::AddLine(glm::vec3 begin, glm::vec3 end, COLORS color)
{
	if (!GizmosEnabled)return;
	LineGizmoShader->Use();

	glBindVertexArray(LineArrayBufferLayout);



	LineArrayBuffer->InsertData(0, sizeof(glm::vec3), &begin[0]);
	LineArrayBuffer->InsertData(sizeof(glm::vec3), sizeof(glm::vec3), &end[0]);


	LineArrayBuffer->Bind();
	glEnableVertexAttribArray(0);



	glDrawArrays(GL_LINES, 0, 3);
}

void Gizmos::AddWireCube(glm::vec3 Pos, glm::vec3 Size)
{

	DrawCubeCmd cmd;
	cmd.SizeData = Size;
	cmd.PosData = Pos;
	DrawCubeCmds.push_back(cmd);

	/*
	if (!GizmosEnabled)return;
	CubeGizmoShader->Use();
	glBindVertexArray(CubeArrayBufferLayout);

	//CubeArrayBuffer->Bind();
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeElementBuffer);
	//glEnableVertexAttribArray(0);
	glUniform3fv(CubePosLoc, 1, &Pos[0]);
	glUniform3fv(CubeSizeLoc, 1, &Size[0]);

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	//glDisableVertexAttribArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
	

}
