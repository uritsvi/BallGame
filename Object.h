#pragma once

#include <memory>

#include "surface.h"
#include "template.h"

class Object
{
public:
	virtual void Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const worldOffset) {};
	
	virtual void PhysicsTick() { };
};

