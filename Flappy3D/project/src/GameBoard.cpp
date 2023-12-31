#include "pch.h"

#include "GameBoard.h"
#include "Timing.h"

GameBoard::GameBoard(unsigned int size) : Inspectable{ "GameBoard"s }, _size{ size }
{
	SetChanged();

	for (auto i{ 0U }; i < _size; i++)
	{
		Push({ true });
	}
}

void GameBoard::Push(const std::vector<bool>& column)
{
	_columns.push_back(column);
}

void GameBoard::Push(const std::vector<std::vector<bool>>& formation)
{
	for (auto& column : formation)
	{
		_columns.push_back(column);
	}
}

void GameBoard::Pop()
{
	_columns.erase(_columns.begin());
}

const std::vector<std::vector<bool>>& GameBoard::GetColumns() const
{
	return _columns;
}

int GameBoard::GetCurrentSize() const
{
	return _columns.size();
}

int GameBoard::GetSize() const
{
	return _size;
}

void GameBoard::InspectImplementation()
{
	ui::InputFloat("movingSpeed", &_movingSpeed);
}

void GameBoard::Update()
{
	if (_movingSpeed == 0.f)
		return;

	_verticalShift += _movingSpeed * _speedMultiplier * Timing::Delta();

	if (_verticalShift >= 1.0f)
	{
		SetChanged();
		_verticalShift -= int(_verticalShift);
		Pop();

		while(_columns.size() < _size)
		{
			if (_runningSpace > _minimalSpace * 1.4f * _speedMultiplier && ci::randInt(4) == 0)
			{
				const auto width{ ci::randInt(int(4.0f * _speedMultiplier)) + 1 };
				const auto height{ ci::randInt(2) + 1 };
				const auto formation{ MakeFormation(height, width) };
				Push(formation);

				_runningSpace = 0;
			}
			else
			{
				Push({ true });

				++_runningSpace;
			}
		}
	}
}

float GameBoard::GetVerticalShift() const
{
	return _verticalShift;
}

bool GameBoard::IsIntersection(ci::vec2 bounds1, ci::vec2 bounds2) const
{
	if (bounds1.y < bounds2.x || bounds1.x > bounds2.y)
	{
		return false;
	}

	return true;
}

bool GameBoard::IsCollision(Player& player) const
{
	return _isCollision;
}

void GameBoard::CalculateCollisions(Player& player)
{
	_isCollision = false;

	const auto center{ _size / 2 };
	const auto left{ center - 1 };
	const auto right{ center + 1 };

	const auto pairityShift{ _size % 2 == 0 ? 0.5f : 0.0f };

	const auto comfortSpace{ 0.05f };
	const auto playerBounds{ ci::vec2{
		center + _verticalShift - pairityShift + comfortSpace,
		1.0f * center + 1.0f + _verticalShift - pairityShift - comfortSpace} };

	const auto makeBounds([](auto& value) {
		return ci::vec2{ value + 0.1f, value + 1.0f - 0.1f };
		});

	for (const auto column : { center, left, right })
	{
		const auto bounds{ makeBounds(column) };
		const auto height{ _columns[column].size() - 1 };

		if (IsIntersection(bounds, playerBounds) && player.GetVerticalPosition() + 0.1f < height)
		{
			_isCollision = true;
		}
	}
}

void GameBoard::UpdateSpeedMultiplier(float multiplier)
{
	_speedMultiplier = multiplier;
}

void GameBoard::Stop()
{
	_movingSpeed = 0.0f;
}

float GameBoard::GetMovingSpeed() const
{
	return _movingSpeed;
}

void GameBoard::Start()
{
	_movingSpeed = defaultMovingSpeed;
}

std::vector<std::vector<bool>> GameBoard::MakeFormation(int height, int width)
{
	std::vector<std::vector<bool>> formation;

	auto size{ 0 };
	for (auto x = 0; x < width; x++)
	{
		formation.push_back({true});
		auto& column{ formation.back() };
		
		for (auto y = 0; y < ci::randInt(height + 1) + 1; y++)
		{
			column.push_back(true);
		}

		size += column.size();
	}

	if (IsFormationHuge(formation))
	{
		auto& column = ci::randInt(2) == 0 ? formation[0] : formation[formation.size() - 1];
		column.pop_back();
	}

	return formation;
}

bool GameBoard::IsFormationHuge(const std::vector<std::vector<bool>>& formation)
{
	return formation.size() > 8;
}
