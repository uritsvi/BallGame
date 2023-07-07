#pragma once

#include <memory>

#include "template.h"
#include "ColiderManager.h"

class Physics;
class Physics;

typedef void(*OnColide)(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p);

struct GravityProperties {
	Tmpl8::vec2 MaxVelocity;
};

class Physics : public std::enable_shared_from_this<Physics>
{
public:
	Physics() = default;

	Physics(
		Tmpl8::vec2& const position,
		Tmpl8::vec2& const scale,
		OnColide Callback,
		void* p);

	void SetAABBColider();
	void SetCircularColider();

	void InitGravity(float maxVelocity);

	void PhysicsColideCallback(
		Collider& c1, 
		Collider& c2,
		CollisionInfo& const info,
		void* p);

	void GetPosition(Tmpl8::vec2& out);
	void GetScale(Tmpl8::vec2& out);

	void AddPosition(Tmpl8::vec2& const position);
	void SetPosition(Tmpl8::vec2& const position);

	void Tick();
	
	void AddVelocity(Tmpl8::vec2& const velocity);
	void SetVelocity(Tmpl8::vec2& const velocity);

	void GetVelocity(Tmpl8::vec2& out);

	bool UseGravity();

private:
	void GetFriction(Tmpl8::vec2& out);

	void ApplyGravity();
	void Accelerate(Tmpl8::vec2& const acceleration);


private:
	bool m_UseGravity;

	std::shared_ptr<Tmpl8::vec2> m_Position;
	std::shared_ptr<Tmpl8::vec2> m_OldPosition;
	
	std::shared_ptr<Tmpl8::vec2> m_Scale;

	std::shared_ptr<Tmpl8::vec2> m_Acceleration;

	std::shared_ptr<Tmpl8::vec2> m_LastTickVelocity;

	
	float m_DeltaTime;

	OnColide m_ColiderCallback;
	void* m_Colider_P;

	float m_MaxVelocity;


private:
	Tmpl8::vec2 m_Gravity = { 0.0f, 1.0f };
};

