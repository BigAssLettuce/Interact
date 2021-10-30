#include "UBO_Binding_Manager.h"
#include "../../../Core/Debug/Console.h"
UBO_Binding_Manager* UBO_Binding_Manager::INSTANCE;
UBO_Binding_Manager::UBO_Binding_Manager()
{
	//BindingPoints = std::vector<std::string>();
	BindingPoints = std::map<std::string, BindingPointElement>();
}
//UBO_Binding_Manager* UBO_Binding_Manager::INSTANCE = nullptr;
UBO_Binding_Manager* UBO_Binding_Manager::GetInstance()
{
	if (!INSTANCE) INSTANCE = new UBO_Binding_Manager();
	return INSTANCE;
}

BindingPointElement UBO_Binding_Manager::RegisterBindingPoint(std::string Name)
{
	LastIndex++;
	BindingPoints.insert(std::pair<std::string, BindingPointElement>(Name, LastIndex));
	Console::Log("Binding Point " + Name + " registered at " + to_string(LastIndex),ConsoleColors::GREEN);

	return LastIndex;

}

BindingPointElement UBO_Binding_Manager::GetBindingPoint(std::string Name)
{
	Console::Log("Binding Point " + Name + " is at " + to_string(BindingPoints.at(Name)), ConsoleColors::GREEN);
	return BindingPoints.at(Name);
}

std::map<std::string, BindingPointElement> UBO_Binding_Manager::GetBindingPoints()
{
	return BindingPoints;
}
