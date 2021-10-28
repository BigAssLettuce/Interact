#include "Camera3D.h"
#include "../../Core/Registry.h"
GLuint Camera3D::CameraDataBufferID = -1;

int Camera3D::CameraDataBufferBindingPoint = -1;


void Camera3D::ComputeTRSViewMatrix()
{  
	mat4 rotmat = mat4(Rotation);
	mat4 posMat = translate(mat4(1.0f), -WS_Pos);

	ViewMat = rotmat * posMat;
}


Camera3D::~Camera3D()
{

}
Camera3D::Camera3D()
{
	if (CameraDataBufferBindingPoint == -1) CameraDataBufferBindingPoint = Registry::RegisterUniform(CameraDataUniform);
	if (CameraDataBufferID == -1) { //IF STATIC UNIFORM BUFFER DOES NOT EXIST
		glCreateBuffers(1, &CameraDataBufferID);
		glBindBuffer(GL_UNIFORM_BUFFER, CameraDataBufferID);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 3 +sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, CameraDataBufferBindingPoint, CameraDataBufferID);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		Console::Log("Camera Data Uniform Buffer ID " + std::to_string(CameraDataBufferID));
	}
}

void Camera3D::GenPersProjMat(float FOV, float Nearclip, float Farclip)
{
	ivec2 windowsize;
	glfwGetFramebufferSize(Window::GlWindowPointer, &windowsize.x, &windowsize.y);
	ProjMat = glm::perspective(glm::radians(FOV), (GLfloat)windowsize.x / (GLfloat)windowsize.y, Nearclip, Farclip);

}

void Camera3D::UpdateBuffer()
{
	mat4 ProjViewMat = ProjMat* ViewMat ;
	float testfloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	ImGui::Begin("Camera3D test");
	
	if (ImGui::BeginTable("table1", 4))
	{
		for (int row = 0; row < 4; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < 4; column++)
			{
				ImGui::TableSetColumnIndex(column);
				ImGui::Text(to_string(ViewMat[column][row]).c_str());
			}
		}
		ImGui::EndTable();
	}
	ImGui::End();
	//Console::Log(to_string(ViewMat));
	glBindBuffer(GL_UNIFORM_BUFFER, CameraDataBufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), &ViewMat[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), &ProjMat[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4) * 2, sizeof(mat4), &ProjViewMat[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4) * 3, sizeof(vec3), &WS_Pos.x);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
