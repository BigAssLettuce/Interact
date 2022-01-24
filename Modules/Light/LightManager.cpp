#ifdef MODULE_LIGHT
#include "LightManager.h"

#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"
LightManager* LightManager::INSTANCE;
LightManager::LightManager()
{
	UBO = new UniformBuffer(UBOSize, DYNAMIC_DRAW);
	UBO->BindBufferBindingPoint(UBO_Binding_Manager::GetInstance()->RegisterBindingPoint(LIGHTDATAUNIFORMNAME,UBOBindingType::STD140));
	//UBO_Binding_Manager* ubmanager = UBO_Binding_Manager::GetInstance();
	//ubmanager->RegisterBindingPoint(LightUniformName);

}

LightManager* LightManager::GetInstance()
{
	if (!INSTANCE) INSTANCE = new LightManager();
	return INSTANCE; 

}

void LightManager::UploadLights()
{

	int index = 0;

	//Console::Log(to_string(index));
	UBO->InsertData(index, sizeof(PointLights), PointLights);//ONLY ADDS THE EXISTING POINTLIGHTS, SKIPS THE REST OF ALLOCATED MEMORY FOR ARRAY
	index += sizeof(PointLights);

	UBO->InsertData(index, sizeof(unsigned int), &PointLightCount);
	index += sizeof(glm::vec4);

	UBO->InsertData(index, sizeof(DirectionalLights), DirectionalLights);
	index += sizeof(DirectionalLights);

	UBO->InsertData(index, sizeof(unsigned int), &DirectionalLightCount);
	index += sizeof(unsigned int);


	
}
#endif