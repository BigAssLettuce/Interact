#pragma once
//#include "../../Core/include.h"
//#include "../../Core/Registry.h"
#include "../../Core/RenderAPI/UniformBindingManager/UBO_Binding_Manager.h"
#include <string>
#include "../../Core/RenderAPI/RenderAPI.h"
#include "../../Core/Debug/Console.h"

enum ShaderTypes {
	VERTEX,
	FRAGMENT,
	GEOMETRY
};

struct ShaderPart {
	ShaderTypes Type;
	std::string Content;
};
class Debugger;
class Shader
{
	friend Debugger;

	std::string ParseUniformBuffers(std::string source) {
		std::string returnstring = source;
		//int pos = 0;
		std::map<std::string, unsigned int> bindingpoints = UBO_Binding_Manager::GetInstance()->GetBindingPoints();
		for (std::pair<std::string, unsigned int> bindingpoint : bindingpoints) {
			size_t loc = returnstring.find("uniform " + bindingpoint.first);
			if (loc != -1) {
				//Debug::Log(to_string(static_cast<int>(loc)));
				returnstring.insert(static_cast<int>(loc), "layout (std140,binding = " + to_string(bindingpoint.second) + ")");
				Console::Log("Added uniform buffer " + bindingpoint.first + " at " + to_string(bindingpoint.second));
			}
			//pos++;
		}
		//Debug::Log(returnstring);
		return returnstring;
	}
	std::vector<ShaderPart> ShaderParts = std::vector<ShaderPart>();
	static std::vector<Shader*> SHADERS;
public:
	std::string Name = "No Name";
	GLint shaderProgramID = glCreateProgram();
	Shader();
	~Shader();
	bool LoadShader(ShaderTypes types[], std::string files[]);
	bool LoadBasicShader(std::string vertex, std::string fragment);
	void Use();

};
