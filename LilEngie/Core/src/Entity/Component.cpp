#include "GameObject.h"
#include "Component.h"

Component::Component(GameObject *obj)
	:obj(obj)
{ }

const GameObject* Component::GetObj()
{
	return obj;
}

void Component::Start()
{ }

void Component::Update()
{ }
