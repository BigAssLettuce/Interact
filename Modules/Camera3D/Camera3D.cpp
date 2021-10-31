#include "Camera3D.h"
//#include "../../Core/Registry.h"



UniformBuffer* Camera3D::UBO;

void Camera3D::ComputeTRSViewMatrix()
{  
	glm::mat4 rotmat = glm::mat4(Rotation);
	glm::mat4 posMat = glm::translate(glm::mat4(1.0f), -Position);

	ViewMat = rotmat * posMat;
}

#define UBOTEST

Camera3D::~Camera3D()
{

}
#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"

Camera3D::Camera3D()
{

	if (!UBO) {
		UBO = new UniformBuffer(UBOsize, DYNAMIC_DRAW);
		UBO->BindBufferBindingPoint(UBO_Binding_Manager::GetInstance()->RegisterBindingPoint(CAMERA3D_UNIFORM_NAME));
	}

	GenPersProjMat(80, 0.1, 15);
	Use();


	
}
#include "../../Core/Application/MainWindow.h"
void Camera3D::GenPersProjMat(float FOV, float Nearclip, float Farclip)
{
	glm::ivec2 windowsize;
	glfwGetFramebufferSize(MainWindow::GlWindowPointer, &windowsize.x, &windowsize.y);
	ProjMat = glm::perspective(glm::radians(FOV), (GLfloat)windowsize.x / (GLfloat)windowsize.y, Nearclip, Farclip);
	zNear = Nearclip;
	zFar = Farclip;

}

void Camera3D::Use()
{
	glm::mat4 ProjViewMat = ProjMat* ViewMat ;
	

	UBO->InsertData(0, sizeof(glm::mat4), &ViewMat[0][0]);
	UBO->InsertData(sizeof(glm::mat4), sizeof(glm::mat4), &ProjMat[0][0]);
	UBO->InsertData(sizeof(glm::mat4) * 2, sizeof(glm::mat4), &ProjViewMat[0][0]);






	//Console::Log(to_string(ViewMat));

}
