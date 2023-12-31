#pragma once

class Changable
{
	bool _hasChanged{ false };

public:
	virtual bool HasChanged() const;

protected:
	virtual void Reset();
	virtual void SetChanged();
};
