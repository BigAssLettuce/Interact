#pragma once
#include<vector>
#include "../../Core/RenderAPI/Buffers/Uniform/UniformBuffer.h"
#include "../../Core/glm.h"


#define MAXLIGHTS 64
#define LightIDVar GLushort

struct PointLight {
	glm::vec3 Color = glm::vec3(1, 1, 1);
	float Intensity = 1;
	glm::vec3 Pos;
	float Radius = 0.5;
	float Range = 5;
	float Attentuation = 1;
	glm::vec2 Padding;
};


struct DirectionalLight {
	glm::vec3 Color = glm::vec3(1, 1, 1);
	float Intensity = 1;
	glm::vec3 Direction = glm::vec3(0,-1,0);

	float padding1=0;


};
class LightManager
{
	friend Debugger;
	
#define LIGHTDATAUNIFORMNAME "LightData"
	
	LightManager();
	static LightManager* INSTANCE;
	


	static const unsigned int UBOSize = (sizeof(PointLight) * MAXLIGHTS +sizeof(glm::vec4)
		+ sizeof(DirectionalLight) * MAXLIGHTS + sizeof(glm::vec4));

	UniformBuffer* UBO;

	unsigned int PointLightCount = 0;
	PointLight PointLights[MAXLIGHTS];


	unsigned int DirectionalLightCount = 0;
	DirectionalLight DirectionalLights[MAXLIGHTS];

	

	

public:
	static LightManager* GetInstance();

	template<typename T>
	void DeleteLight(T) {
		//if (static_cast<T>(Light)) assert("Light to delete must be child of Light Class. Eg: PointLight");
		switch (T)
		{
		default:
			break;
		}
	}

	PointLight* NewPointLight() { 
		PointLights[PointLightCount]= PointLight();
		PointLightCount++;
		return &PointLights[PointLightCount - 1]; }

	DirectionalLight* NewDirectionalLight() {
		DirectionalLights[DirectionalLightCount] = DirectionalLight();
		DirectionalLightCount++;
		return &DirectionalLights[DirectionalLightCount - 1];
	}

	void UploadLights();

};

