#pragma once

class Inputable
{
public:
	virtual void OnInput(const ci::app::KeyEvent& event) = 0;
};
