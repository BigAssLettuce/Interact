#pragma once
#include <vector>
#include <string>
#include <map>
#define BindingPointElement unsigned int

enum UBOBindingType {
	STD140,
	SHARED,
	PACKED,
	STD430
};
static class UBO_Binding_Manager
{
	UBO_Binding_Manager();
	static UBO_Binding_Manager* INSTANCE;
	//std::vector<std::string> BindingPoints;
	std::map<std::string, BindingPointElement> BindingPoints;
	BindingPointElement LastIndex = -1;

public:
	static UBO_Binding_Manager* GetInstance();
	BindingPointElement RegisterBindingPoint(std::string Name);
	BindingPointElement GetBindingPoint(std::string Name);
	std::map<std::string, BindingPointElement> GetBindingPoints();
	

};

