#pragma once

#include <memory>

#include "surface.h"
#include "template.h"

#include "Level.h"

class Camera
{
public:
	Camera();

	void Draw(
		Tmpl8::Surface& target, 
		Level& const level);

	void AddPositionOffset(Tmpl8::vec2 offset);

private:
	std::shared_ptr<Tmpl8::vec2> m_Position;
};

