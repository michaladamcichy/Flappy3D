#pragma once

#include "Inspectable.h"
#include "Updatable.h"

class Camera : public ci::CameraPersp, public Inspectable, public Updatable
{
	ci::vec3 _position{ 0.0f, 3.0f, 10.0f };
	ci::vec3 _rotation{ 0.0f, 0.0f, 0.0f };
	ci::vec3 _direction{ 0.0f, 0.0f, -1.0f };

public:
	constexpr static float defaultFov{ 70.0f };
	constexpr static float defaultNear{ 0.01f };
	constexpr static float defaultFar{ 100000000.0f };

	Camera();

	virtual void Update() override;

private:
	virtual void InspectImplementation() override;
};
