#pragma once

#include <memory>

#include "Object.h"
#include "Render.h"
#include "Physics.h"
#include "Camera.h"
#include "Colliders.h"

class Ball : public Object
{
public:
	Ball() = default;

	Ball(
		int textureIndex,
		Tmpl8::vec2 position,
		Tmpl8::vec2 scale);

	void Draw(
		Tmpl8::Surface& target,
		Tmpl8::vec2& const position);
	
	void PhysicsTick() override;
	
	void Jump();
	void MoveLeft();
	void MoveRight();

	void Tick(Camera& const camera);

	void OnColideCallback(
		Collider& const c1,
		Collider& const c2,
		CollisionInfo& const info,
		void* p);

	void SetPosition(Tmpl8::vec2& const position);

	void Reset();

private:
	Tmpl8::vec2 m_WorldOffset;
	Tmpl8::vec2 m_StartPosition;

	std::shared_ptr<Render> m_Render;
	std::shared_ptr<Physics> m_Physics;

	Direction m_LastCollideSide;

	int m_NumOfJumps;
};

