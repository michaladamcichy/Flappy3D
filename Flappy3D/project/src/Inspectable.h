#pragma once

class Inspectable
{
protected:
	std::string _name;

public:
	Inspectable(std::string name);

	virtual void Inspect();

protected:
	virtual void InspectImplementation() = 0;
};
