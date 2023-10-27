#pragma once

#include "Drawable.h"
#include "Inspectable.h"
#include "Setupable.h"

#include "Personalizator.h"

class Gui : public Setupable, public Drawable, public Inspectable
{
	static Gui* _instance;
	std::vector<Inspectable*> _inspectables;
	std::function<void()> _onQuitClicked;
	bool _startClicked{ false };

	int _fps{ 0 };
	int _score{ 0 };
	
	Personalizator _personalizator;

	bool _showInspector{ false };
	bool _showPersonalizator{ false };

public:
	static Gui* GetInstance();
	static bool SmartSliderFloat3(std::string label, ci::vec3& variable);
	
	Gui();

	void Setup() override;
	void Draw() override;
	void Inspect() override;

	void AddInspectable(Inspectable* inspectable);
	void SetOnQuitClicked(std::function<void()> action);

	Personalizator::Matrix GetPersonalizedPlayerData() const;
	ci::Color GetPersonalizedPlayerColor() const;
	bool HasPlayerDataChanged() const;

	void UpdateScore(int score);
	void UpdateFps(int fps);
	void ShowPersonalizator();
	void HidePersonalizator();

private:
	void DrawTopMenu();
	void DrawInspector();
	void DrawPersonalizator();
	void InspectImplementation() override;
};
