#include "UBO_Binding_Manager.h"
#include "../../../Core/Debug/Console.h"
UBO_Binding_Manager* UBO_Binding_Manager::INSTANCE;
UBO_Binding_Manager::UBO_Binding_Manager()
{
	//BindingPoints = std::vector<std::string>();
	BindingPoints = std::map<std::string, BindingPoint>();
}
//UBO_Binding_Manager* UBO_Binding_Manager::INSTANCE = nullptr;
UBO_Binding_Manager* UBO_Binding_Manager::GetInstance()
{
	if (!INSTANCE) INSTANCE = new UBO_Binding_Manager();
	return INSTANCE;
}

BindingPointElement UBO_Binding_Manager::RegisterBindingPoint(std::string Name,UBOBindingType type)
{
	LastIndex++;
	BindingPoint bPoint;
	bPoint.point = LastIndex;
	bPoint.type = type;
	BindingPoints.insert(std::pair<std::string, BindingPoint>(Name, bPoint));
	Console::Log("Binding Point " + Name + " registered at " + to_string(LastIndex) +"With type: " + to_string(type), COLORS::GREEN);

	return LastIndex;

}

BindingPoint UBO_Binding_Manager::GetBindingPoint(std::string Name)
{
	Console::Log("Binding Point " + Name + " is at " + to_string(BindingPoints.at(Name).point), COLORS::GREEN);
	return BindingPoints.at(Name);
}

std::map<std::string, BindingPoint> UBO_Binding_Manager::GetBindingPoints()
{
	return BindingPoints;
}
