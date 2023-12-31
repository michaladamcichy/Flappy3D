#pragma once

#include "Inspectable.h"
#include "Updatable.h"
#include "Changable.h"

#include "Player.h"

class GameBoard : public Inspectable, public Updatable, public Changable
{
	static constexpr float defaultMovingSpeed{ 5.0f };
	static constexpr int _minimalSpace{ 3 };
	
	unsigned int _size{ 0 };
	float _speedMultiplier{ 1.0f };
	float _verticalShift{ 0.0f };
	float _movingSpeed{ 0.0f };

	int _runningSpace{ 0 };
	bool _isCollision{ false };

	std::vector<std::vector<bool>> _columns;

public:
	GameBoard(unsigned int size);

	void Push(const std::vector<bool>& column);
	void Push(const std::vector<std::vector<bool>>& formation);
	void Pop();

	const std::vector<std::vector<bool>>& GetColumns() const;
	int GetCurrentSize() const;
	int GetSize() const;
	float GetVerticalShift() const;
	float GetMovingSpeed() const;
	
	bool IsIntersection(ci::vec2 bounds1, ci::vec2 bounds2) const;
	bool IsCollision(Player& player) const;


	void Start();
	void Stop();
	void UpdateSpeedMultiplier(float multiplier);
	void CalculateCollisions(Player& player);
	void Update() override;

private:
	void InspectImplementation() override;
	
	static std::vector<std::vector<bool>> MakeFormation(int height, int width);
	static bool IsFormationHuge(const std::vector<std::vector<bool>>& formation);
};
