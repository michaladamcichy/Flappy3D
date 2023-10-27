#include "pch.h"

#include "Material.h"

Material::Material(std::string _textureName, float _reflectiveness, ci::Color _color) :
	textureName{ _textureName },
	reflectiveness{ _reflectiveness },
	color{ _color } {}
