#include "pch.h"
#include "SatellitesBatch.h"
#include "Timing.h"

SatellitesBatch::SatellitesBatch(const Material& material, Bindable* environmentalMap) : Batch{material, environmentalMap}
{
}

void SatellitesBatch::Setup()
{
	Batch::Setup();

	std::vector<std::unique_ptr<GameObject>> satellites;
	satellites.reserve(_chainLength + _chainLength % 2 == 0 ? 1 : 0);

	for (auto x{ -_chainLength / 2 }; x <= _chainLength / 2; x++)
	{
		satellites.push_back(std::make_unique<GameObject>(ci::vec3(1.0f * x, 0.0f, _radius), ci::vec3{_satelliteSize}));
		satellites.back()->RotateAroundAxis(1.0f * x * _angleOffset, Constants::Axis::x);
	}

	UpdateBuffer(satellites, true);
}

void SatellitesBatch::Update()
{
	const auto angle{ _rotationSpeedMultiplier * _rotationSpeed * Timing::Delta() };
	RotateAroundAxis( angle, Constants::Axis::x);
}

void SatellitesBatch::UpdateSpeed(float speed)
{
	_rotationSpeedMultiplier = speed;
}
