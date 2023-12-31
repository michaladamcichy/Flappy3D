#include "pch.h"

#include "Personalizator.h"

#include "Gui.h"

Personalizator::Personalizator() : Inspectable{ "Personalizator"s }
{
	Initialize();
}


void Personalizator::InspectImplementation()
{
	Reset();

	if (ui::Button("Close"))
		Gui::GetInstance()->HidePersonalizator();

	ui::Spacing();

	if (ui::Button("Save to file"))
		SaveToFile();

	ui::Spacing();

	if (ui::ColorPicker3("Player color", &_color[0]))
	{
		SetChanged();
	}

	ui::Spacing();
	
	for (auto y{ 0 }; y < _height; y++)
	{
		bool firstInRow = true;
		for (auto x{ 0 }; x < _width; x++)
		{
			if (!firstInRow)
				ui::SameLine();
			else
				firstInRow = false;

			auto label{ std::to_string(y * _width + x) };
			if (label.size() == 1)
				label = " " + label;
			
			if (ui::Checkbox(label.c_str(), &_playerShape[y][x]))
			{
				SetChanged();
			}
		}
	}
}

void Personalizator::Inspect()
{
	ui::Begin(_name.c_str());
	InspectImplementation();
	ui::End();
}

void Personalizator::Initialize()
{
	try
	{
		LoadFromFile();
	}
	catch (...) 
	{
		for(auto& row : _playerShape)
			for (auto& item : row)
			{
				item = true;
			}
	}
}

Personalizator::Matrix Personalizator::GetPlayerData() const
{
	return _playerShape;
}

ci::Color Personalizator::GetPlayerColor() const
{
	return _color;
}

void Personalizator::LoadFromFile()
{
	std::ifstream in;
	in.open(fileName);

	if (!in.good())
	{
		throw std::exception{"File not found"};
	}

	in >> _color.r;
	in >> _color.g;
	in >> _color.b;


	for (auto y{ 0 }; y < _height; y++)
	{
		for (auto x{ 0 }; x < _width; x++)
		{
			in >> _playerShape[y][x];
		}
	}
}

void Personalizator::SaveToFile()
{
	std::ofstream out;
	out.open(fileName);

	out << _color.r << std::endl;
	out << _color.g << std::endl;
	out << _color.b << std::endl;


	for (auto y{ 0 }; y < _height; y++)
	{
		for (auto x{ 0 }; x < _width; x++)
		{
			out << _playerShape[y][x];
			if (x < _width - 1)
				out << " ";
		}
		if (y < _height - 1)
			out << std::endl;
	}

	out.close();
}
