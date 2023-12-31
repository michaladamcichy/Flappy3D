#pragma once

#include "Inspectable.h"
#include "Inputable.h"
#include "Updatable.h"
#include "Changable.h"

class Player : public Inspectable, public Inputable, public Updatable, public Changable
{
	float _jumpHeight{ 7.0f };
	float _jumpDuration{ 1.0f };

	ci::vec2 _dimensions{1.0f, 2.0f};
	ci::Anim<float> _verticalPosition{ 0.f };

	ci::Anim<bool> _jumpQueued{ false };
	bool _isDead{ false };

public:
	Player();

	int GetWidth() const;
	int GetHeight() const;
	float GetVerticalPosition() const;
	bool CanJump() const;
	bool IsDead() const;

	void Kill();
	void Jump();
	void QueueJump();
	void UnqueueJump();

	void Update() override;
	void OnInput(const ci::app::KeyEvent& event) override;

private:
	void InspectImplementation() override;
};
