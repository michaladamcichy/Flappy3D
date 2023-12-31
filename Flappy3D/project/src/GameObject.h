#pragma once

#include "Drawable.h"
#include "Inspectable.h"

#include "TransformableObject.h"

class GameObject : public TransformableObject, public Inspectable
{
public:
	GameObject(ci::vec3 position = { 0.f, 0.f, 0.f }, ci::vec3 scale = { 1.0f, 1.0f, 1.0f });

private:
	void InspectImplementation() override;
};
