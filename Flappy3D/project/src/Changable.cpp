#include "Changable.h"

bool Changable::HasChanged() const
{
	return _hasChanged;
}

void Changable::Reset()
{
	_hasChanged = false;
}

void Changable::SetChanged()
{
	_hasChanged = true;
}
