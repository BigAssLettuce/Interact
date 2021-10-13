#include "Shader.h"
 

bool CompileSuccess(int Shader, string* Info) {
	int success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		*Info = infoLog;
		return false;
	}
	return true;
}
bool LinkSuccess(int Program, string* Info) {
	int success;
	char infoLog[512];
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		*Info = infoLog;
		return false;
	}
	return true;
}

Shader::Shader()
{
	Debug::Log("Shader program ID: " + std::to_string(shaderProgramID));
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgramID);
}

bool Shader::LoadBasicShader(string vertexFile, string fragmentFile) //loads from Resources/Shaders/
{
	string vertexfilepath = vertexFile;
	string fragmentfilepath = fragmentFile;
	string vsSource;
	if (!Resource::ReadTextFile(vertexfilepath, &vsSource)) return false;
	ParseUniformBuffers(vsSource);
	const char* vsSourceTemp = vsSource.c_str();

	string fsSource;
	if (!Resource::ReadTextFile(fragmentfilepath, &fsSource)) return false;
	ParseUniformBuffers(fsSource);
	const char* fsSourceTemp = fsSource.c_str();

	int vsShader = glCreateShader(GL_VERTEX_SHADER);
	int fsShader = glCreateShader(GL_FRAGMENT_SHADER);

	string CompileLog;
	glShaderSource(vsShader, 1,&vsSourceTemp, NULL);
	glCompileShader(vsShader);
	if (!CompileSuccess(vsShader, &CompileLog)) Debug::Error("Shader " + vertexFile + " Compile Failed\n" + CompileLog);

	glShaderSource(fsShader, 1, &fsSourceTemp, NULL);
	glCompileShader(fsShader);
	if (!CompileSuccess(fsShader, &CompileLog)) Debug::Error("Shader " + fragmentFile + " Compile Failed\n" + CompileLog);

	glAttachShader(shaderProgramID, vsShader);
	glAttachShader(shaderProgramID, fsShader);
	glLinkProgram(shaderProgramID);
	if (!LinkSuccess(shaderProgramID, &CompileLog)) Debug::Error("ShaderProgram " + to_string(shaderProgramID) + " Link Failed\n" + CompileLog);
	glValidateProgram(shaderProgramID);

	glDetachShader(shaderProgramID, vsShader);
	glDetachShader(shaderProgramID, fsShader);

	glDeleteShader(vsShader);
	glDeleteShader(fsShader);

	CheckForUniformBuffers();
	return true;
}

void Shader::Use(){ glUseProgram(shaderProgramID); }
