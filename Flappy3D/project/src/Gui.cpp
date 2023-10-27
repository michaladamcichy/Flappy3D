#include "pch.h"

#include "Gui.h"

#include "Timing.h"

Gui::Gui() : Inspectable("Inspector") {}

void Gui::Setup()
{
	_instance = this;

	ui::initialize();
	ui::StyleColorsDark();
}

void Gui::Draw()
{
	DrawTopMenu();

	if (_showInspector)
		DrawInspector();

	if (_showPersonalizator)
		DrawPersonalizator();
}

void Gui::DrawTopMenu()
{
	if (ui::BeginMainMenuBar())
	{
		if (ui::Button("Quit"))
		{
			_onQuitClicked();
		}

		if (ui::Button("Personalize"))
		{
			_showPersonalizator = true;
		}

		ui::Spacing();

		ui::Text(("Score: "s + std::to_string(_score)).c_str());
		ui::Text(("Fps: "s + std::to_string(_fps)).c_str());

		ui::Spacing();

		ui::EndMainMenuBar();
	}
}

void Gui::DrawInspector()
{
	Inspect();
}

Gui* Gui::GetInstance()
{
	return _instance;
}	

void Gui::Inspect()
{
	ui::Begin(_name.c_str());
	InspectImplementation();
	ui::End();
}

void Gui::UpdateScore(int score)
{
	_score = score;
}

void Gui::UpdateFps(int fps)
{
	_fps = fps;
}

void Gui::ShowPersonalizator()
{
	_showPersonalizator = true;
}

void Gui::HidePersonalizator()
{
	_showPersonalizator = false;
}

void Gui::InspectImplementation()
{
	for (auto inspectable : _inspectables)
	{
		inspectable->Inspect();
	}
}

void Gui::AddInspectable(Inspectable* inspectable)
{
	_inspectables.push_back(inspectable);
}

Personalizator::Matrix Gui::GetPersonalizedPlayerData() const
{
	return _personalizator.GetPlayerData();
}

ci::Color Gui::GetPersonalizedPlayerColor() const
{
	return _personalizator.GetPlayerColor();
}

bool Gui::HasPlayerDataChanged() const
{
	return _personalizator.HasChanged();
}

void Gui::SetOnQuitClicked(std::function<void()> action)
{
	_onQuitClicked = action;
}

bool Gui::SmartSliderFloat3(std::string label, ci::vec3& variable)
{
	const auto minMax{ 0.2 + std::max({ std::abs(variable.x), std::abs(variable.y), std::abs(variable.z) }) };
	
	return ui::SliderFloat3(label.c_str(), &variable.x, -minMax, minMax);
}

void Gui::DrawPersonalizator()
{
	_personalizator.Inspect();
}

Gui* Gui::_instance{ nullptr };