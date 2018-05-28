#pragma once

#include <string>
#include <Entity/Component.h>

class Mesh : public Component
{
public:
	//Standard component calls
	static std::string GetTypeStatic() { return "Mesh"; }
	std::string GetType() { return GetTypeStatic(); }
	void* GetComponent() { return this; }
};

//CLASS NEEDS WORK