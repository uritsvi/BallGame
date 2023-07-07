#pragma once

#include <memory>

#include "surface.h"
#include "template.h"

#include "Render.h"
#include "Physics.h"

#include "Object.h"

class SolidEntity : public Object
{
public:
	SolidEntity(
		Tmpl8::vec2 position,
		Tmpl8::vec2 scale,
		int textureIndex);

	void Draw(
		Tmpl8::Surface& target, 
		Tmpl8::vec2& const worldOffset);

private:
	std::shared_ptr<Render> m_Render;
	std::shared_ptr<Physics> m_Physics;
};

