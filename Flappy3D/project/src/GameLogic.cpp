#include "pch.h"

#include "GameLogic.h"
#include "Timing.h"
#include "Gui.h"

GameLogic::GameLogic() : Inspectable("GameLogic")
{
}

void GameLogic::Setup()
{
	ci::randSeed(randomSeed);
}

void GameLogic::Update()
{
	if (_gameBoard.GetMovingSpeed() == 0.0f)
		return;

	_gameBoard.CalculateCollisions(_player);
	_gameBoard.Update();
	_gameBoard.UpdateSpeedMultiplier(_gameSpeed);
	_player.Update();

	if (!_player.IsDead() && _gameBoard.IsCollision(_player))
	{
		_player.Kill();
		_gameBoard.Stop();
		
		ci::app::timeline().add([&]() { Restart(); }, ci::app::getElapsedSeconds() + _deathDuration);
	}

	HandleGameSpeed();

	Gui::GetInstance()->UpdateScore(_score);
}

void GameLogic::InspectImplementation()
{
	_player.Inspect();
	_gameBoard.Inspect();
}

void GameLogic::OnInput(const ci::app::KeyEvent& event)
{
	if (!_player.IsDead() && 
		_gameBoard.GetMovingSpeed() == 0.0f && 
		event.getCode() == ci::app::KeyEvent::KEY_SPACE)
	{
		Start();
		return;
	}

	_player.OnInput(event);
}

const GameBoard& GameLogic::GetBoard() const
{
	return _gameBoard;
}

const Player& GameLogic::GetPlayer() const
{
	return _player;
}

void GameLogic::Start()
{
	Restart();
	_gameBoard.Start();
}

void GameLogic::Restart()
{
	_player = Player{};
	_gameBoard = GameBoard( defaultGameBoardSize );
	_gameSpeed = 1.0f;
	_score = 0;
}

float GameLogic::GetGameSpeed() const
{
	return _gameSpeed;
}

void GameLogic::HandleGameSpeed()
{
	_timeToAdvanceSpeed -= Timing::Delta();
	if (_timeToAdvanceSpeed <= 0.0f)
	{
		_gameSpeed += 0.1f;
		_timeToAdvanceSpeed = _advanceSpeedInterval;	

		OnGameSpeedChange();
	}
}

void GameLogic::OnGameSpeedChange()
{
	_score++;
}
