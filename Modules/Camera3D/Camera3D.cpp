#include "Camera3D.h"
//#include "../../Core/Registry.h"



UniformBuffer* Camera3D::UBO;

void Camera3D::ComputeTRSViewMatrix()
{  
	mat4 rotmat = mat4(Rotation);
	mat4 posMat = translate(mat4(1.0f), -WS_Pos);

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




	
}

void Camera3D::GenPersProjMat(float FOV, float Nearclip, float Farclip)
{
	ivec2 windowsize;
	glfwGetFramebufferSize(Window::GlWindowPointer, &windowsize.x, &windowsize.y);
	ProjMat = glm::perspective(glm::radians(FOV), (GLfloat)windowsize.x / (GLfloat)windowsize.y, Nearclip, Farclip);

}

void Camera3D::Use()
{
	mat4 ProjViewMat = ProjMat* ViewMat ;
	

	UBO->InsertData(0, sizeof(mat4), &ViewMat[0][0]);
	UBO->InsertData(sizeof(mat4), sizeof(mat4), &ProjMat[0][0]);
	UBO->InsertData(sizeof(mat4)*2, sizeof(mat4), &ProjViewMat[0][0]);






	//Console::Log(to_string(ViewMat));

}
