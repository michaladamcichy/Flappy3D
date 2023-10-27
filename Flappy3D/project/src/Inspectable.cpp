#include "pch.h"
#include "Inspectable.h"
#include"Gui.h"

Inspectable::Inspectable(std::string name) : _name(name)
{
	
}

void Inspectable::Inspect()
{
	if (ui::TreeNode(_name.c_str()))
	{
		InspectImplementation();

		ui::TreePop();
	}
}
