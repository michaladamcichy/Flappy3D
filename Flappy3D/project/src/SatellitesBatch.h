#pragma once

#include "Batch.h"
#include "Updatable.h"

class SatellitesBatch : public Batch, public Updatable
{
	float _rotationSpeed{ 3.0f};
	float _rotationSpeedMultiplier{ 1.0f};
	float _satelliteSize{ 0.6f };
	float _radius{ 8.0f };
	float _angleOffset{ 20.0f };
	int _chainLength{ 30 };

public:
	SatellitesBatch(const Material& material, Bindable* environmentalMap = nullptr);

	void Setup() override;
	void Update() override;

	void UpdateSpeed(float speed);
};
