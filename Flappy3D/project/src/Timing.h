#pragma once

class Timing
{
	static float _last;
	static float _delta;
	
public:

	static void Update();
	static float Delta();
};
