#pragma once

#include "Inspectable.h"
#include "Changable.h"

class Personalizator : public Inspectable, public Changable
{
	static constexpr int defaultWidth{ 5 };
	static constexpr int defaultHeight{ 10 };

	static constexpr const char* fileName{"personalizator"};

	int _width{ defaultWidth };
	int _height{ defaultHeight };

	ci::Color _color{ 1.0f, 155.0f / 255, 0.0f };
	std::array<std::array<bool, defaultWidth>, defaultHeight> _playerShape;

public:
	using Matrix = std::array<std::array<bool, defaultWidth>, defaultHeight>;
	
	Personalizator();
	void InspectImplementation() override;
	void Inspect() override;
	void Initialize();

	Matrix GetPlayerData() const;
	ci::Color GetPlayerColor() const;

	void LoadFromFile();
	void SaveToFile();
};
