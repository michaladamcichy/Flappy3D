#pragma once

#include "Setupable.h"
#include "Updatable.h"
#include "Inputable.h"
#include "Inspectable.h"

#include "Player.h"
#include "GameBoard.h"

class GameLogic : public Setupable, public Updatable, public Inspectable, public Inputable
{
	constexpr static int randomSeed{ 10 };
	constexpr static int defaultGameBoardSize{ 40 };
	constexpr static float _deathDuration{ 2.0f };
	constexpr static float _advanceSpeedInterval{ 2.0f };

	Player _player;
	float _timeToRestart{ -_deathDuration };
	bool _shouldRestart = false;
	float _gameSpeed{ 1.0f };
	
	GameBoard _gameBoard{ defaultGameBoardSize };
	
	int _score{ 0 };
	float _timeToAdvanceSpeed{_advanceSpeedInterval};

public:
	GameLogic();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void OnInput(const ci::app::KeyEvent& event) override;

	const GameBoard& GetBoard() const;
	const Player& GetPlayer() const;
	
	float GetGameSpeed() const;

private:
	void Start();
	void Restart();
	void OnGameSpeedChange();
	void HandleGameSpeed();
	virtual void InspectImplementation();
};
