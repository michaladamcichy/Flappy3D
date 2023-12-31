#include "pch.h"

#include "Timing.h"

void Timing::Update()
{
	const auto _current = ci::app::getElapsedSeconds();
	_delta = _current - _last;
	_last = _current;
}

float Timing::Delta()
{
	return _delta;
}

float Timing::_last = 0.0f;
float Timing::_delta = 1.0f;