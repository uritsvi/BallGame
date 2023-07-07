#pragma once

#include <string>


#include "surface.h"
#include "template.h"

#include "Render.h"
#include "Physics.h"

#include "Object.h"

class DamageEntiy;

typedef void (*OnTouchDamageEntity)(
	DamageEntiy& entity, 
	void* p);

class DamageEntiy : public Object
{
public:
	DamageEntiy(
		Tmpl8::vec2 position,
		Tmpl8::vec2 scale,
		int textureIndex,
		OnTouchDamageEntity callback,
		void* p);

	void Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const worldOffset);

	void CollideCallack(
		Collider& c1,
		Collider& c2,
		CollisionInfo& const info,
		void* p);

private:
	std::shared_ptr<Render> m_Render;
	std::shared_ptr<Physics> m_Physics;

	OnTouchDamageEntity m_Callback;

	void* m_P;
};

