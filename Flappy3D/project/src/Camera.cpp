#include "pch.h"

#include "Camera.h"
#include "Gui.h"

Camera::Camera() : Inspectable("Camera")
{
}

void Camera::InspectImplementation()
{
	Gui::SmartSliderFloat3("position", _position);
	ui::DragFloat3("rotation", &_rotation.x, 1.0f, -180, 180);
}

void Camera::Update()
{
	setPerspective(defaultFov, ci::app::getWindowAspectRatio(), Camera::defaultNear, Camera::defaultFar);
	setOrientation(ci::vec3{ glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z) });
	setEyePoint(_position);
}
