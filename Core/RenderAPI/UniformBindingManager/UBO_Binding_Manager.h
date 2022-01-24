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

struct BindingPoint {
	BindingPointElement point;
	UBOBindingType type;
};
static class UBO_Binding_Manager
{
	UBO_Binding_Manager();
	static UBO_Binding_Manager* INSTANCE;
	//std::vector<std::string> BindingPoints;
	std::map<std::string, BindingPoint> BindingPoints;
	BindingPointElement LastIndex = -1;

public:
	static UBO_Binding_Manager* GetInstance();
	BindingPointElement RegisterBindingPoint(std::string Name,UBOBindingType type );
	BindingPoint GetBindingPoint(std::string Name);
	UBOBindingType GetBindingType(std::string Name);
	std::map<std::string, BindingPoint> GetBindingPoints();
	static std::string ParseType(UBOBindingType type) {
		std::string returningstring;

		switch (type)
		{
		case STD140:
			returningstring = "std140";
			break;
		case SHARED:
			returningstring = "shared";
			break;
		case PACKED:
			returningstring = "packed";
			break;
		case STD430:
			returningstring = "std430";
			break;

		}
		return returningstring;

	}

};

