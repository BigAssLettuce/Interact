#pragma once
#include "include.h"
static class Registry {
	static vector<string> UniformBuffers;

public:
	static vector<string>GetUniformBuffers() { return UniformBuffers; }
	static int RegisterUniform(string ParseName) {
		int BindingPoint = UniformBuffers.size();
		UniformBuffers.push_back(ParseName);
		Debug::Log("Registered Uniform Buffer (" + ParseName + ") at Binding Point " + to_string(BindingPoint));
		return BindingPoint;

	}
};