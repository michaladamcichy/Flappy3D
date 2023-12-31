#include "pch.h"

#include "Player.h",

Player::Player() : Inspectable{ "Player"s }
{
	SetChanged();
}
int Player::GetWidth() const
{ 
	return _dimensions.x;
}

int Player::GetHeight() const 
{ 
	return _dimensions.y;
}

float Player::GetVerticalPosition() const
{ 
	return _verticalPosition; 
}

bool Player::CanJump() const
{
	return !_isDead && _verticalPosition == 0.0f;
}

bool Player::IsDead() const
{
	return _isDead;
}

void Player::Jump()
{
	UnqueueJump();
	ci::app::timeline().apply(&_verticalPosition, _jumpHeight, _jumpDuration / 2, ci::EaseOutCubic());
	ci::app::timeline().appendTo(&_verticalPosition, 0.0f, _jumpDuration / 2 , ci::EaseInCubic());
}

void Player::QueueJump()
{
	_jumpQueued = true;

	ci::app::timeline().add([&]() { _jumpQueued = false; }, ci::app::getElapsedSeconds() + _jumpDuration / 4);
}

void Player::UnqueueJump()
{
	if(!_jumpQueued.isComplete())
		_jumpQueued.stop();
	_jumpQueued = false;
}

void Player::InspectImplementation()
{
	ui::InputFloat("jumpHeight", &_jumpHeight);
	ui::InputFloat("jumpDuration", &_jumpDuration);
	ui::SliderFloat("verticalPosition", &_verticalPosition.value(), 0, _jumpHeight);
}

void Player::OnInput(const ci::app::KeyEvent& event)
{
	if (event.getCode() == ci::app::KeyEvent::KEY_SPACE)
	{
		if (CanJump())
			Jump();
		else
			QueueJump();
	}
}

void Player::Update()
{
	Reset();

	if (CanJump() && _jumpQueued)
	{
		Jump();
	}
}

void Player::Kill()
{
	_isDead = true;
	_verticalPosition.stop();
}
