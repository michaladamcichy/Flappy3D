#include "pch.h"

#include "GameObject.h"
#include "Gui.h"

GameObject::GameObject(ci::vec3 position, ci::vec3 scale) :
	TransformableObject{ scale, position },
	Inspectable("GameObject"s)
{
}

void GameObject::InspectImplementation()
{
}