#include "Camera.h"
//#include "../../Core/Registry.h"
vector<Camera*> Camera::CAMERAS = vector<Camera*>();


UniformBuffer* Camera::UBO;

void Camera::ComputeTRSViewMatrix()
{  
	glm::mat4 rotmat = glm::mat4(Rotation);
	glm::mat4 posMat = glm::translate(glm::mat4(1.0f), -Position);

	ViewMat = rotmat * posMat;
}

#define UBOTEST

Camera::~Camera()
{

}
#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"

Camera::Camera()
{

	if (!UBO) {
		UBO = new UniformBuffer(UBOsize, DYNAMIC_DRAW);
		UBO->BindBufferBindingPoint(UBO_Binding_Manager::GetInstance()->RegisterBindingPoint(CAMERA3D_UNIFORM_NAME));
	}
	CAMERAS.push_back(this);
	GenPersProjMat(80, 0.1, 15);
	Use();


	
}
#include "../../Core/Application/Application.h"
void Camera::GenPersProjMat(float FOV, float Nearclip, float Farclip)
{
	glm::ivec2 windowsize;
	glfwGetFramebufferSize(Application::MainWindow.GLWindowPointer, &windowsize.x, &windowsize.y);
	ProjMat = glm::perspective(glm::radians(FOV), (GLfloat)windowsize.x / (GLfloat)windowsize.y, Nearclip, Farclip);
	Console::Log(to_string(windowsize));
	zNear = Nearclip;
	zFar = Farclip;

}

void Camera::Use()
{
	glm::mat4 ProjViewMat = ProjMat* ViewMat ;
	

	UBO->InsertData(0, sizeof(glm::mat4), &ViewMat[0][0]);
	UBO->InsertData(sizeof(glm::mat4), sizeof(glm::mat4), &ProjMat[0][0]);
	UBO->InsertData(sizeof(glm::mat4) * 2, sizeof(glm::mat4), &ProjViewMat[0][0]);
	UBO->InsertData(sizeof(glm::mat4) * 3, sizeof(glm::vec3), &Position.x);





	//Console::Log(to_string(ViewMat));

}
