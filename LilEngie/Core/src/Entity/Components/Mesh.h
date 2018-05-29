#pragma once

#include <string>
#include <Entity/Component.h>

class Mesh : public Component
{
public:
	//X is just a sample var for testing
	int x;

	Mesh(GameObject *obj);

	//Standard component methods
	static std::string GetTypeStatic() { return "Mesh"; }
	std::string GetType() { return GetTypeStatic(); }
	void* Get() { return this; }
};
