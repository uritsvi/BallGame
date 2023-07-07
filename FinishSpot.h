#pragma once

#include <memory>

#include "Colliders.h"
#include "Physics.h"
#include "Render.h"
#include "Object.h"

#include "template.h"

struct LevelIndex;
class Level;

typedef void(*OnEnter)(
	LevelIndex& levelIndex, 
	void* p);

class FinishSpot : public Object
{
public:
	FinishSpot(
		std::shared_ptr<Level> level,
		OnEnter callback,
		void* p,
		Tmpl8::vec2& position,
		Tmpl8::vec2& scale,
		int textureIndex);

	void Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const worldOffset);

	void OnColideFinishSpot(
		Collider& c1,
		Collider& c2,
		CollisionInfo& const info,
		void* p);

private:
	std::shared_ptr<Physics> m_Physics;
	
	OnEnter m_OnEnter;
	std::shared_ptr<Level> m_Level;

	std::shared_ptr<Render> m_Render;

	void* m_P;
};

