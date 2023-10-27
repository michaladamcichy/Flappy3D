#pragma once

struct Material
{
	std::string textureName;
	float reflectiveness{ 0.0 };
	ci::Color color{ 1.0f, 1.0f, 1.0f };

	Material(std::string __textureName, float __reflectiveness, ci::Color __color = { 1.0f, 1.0f, 1.0f });
};
