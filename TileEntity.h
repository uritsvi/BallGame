#pragma once

#include "Object.h"
#include "Render.h"

#include "template.h"

class TileEntity : public Object
{
public:
	TileEntity(
		Tmpl8::vec2 position,
		Tmpl8::vec2 scale,
		int textureIndex);

	void Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const worldOffset);

private:
	std::shared_ptr<Render> m_Render;
	std::shared_ptr<Tmpl8::vec2> m_Position;
};
