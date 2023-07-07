#include "Physics.h"
#include "Constants.h"

#include <iostream>

Physics::Physics(
	Tmpl8::vec2& const position,
	Tmpl8::vec2& const scale,
	OnColide colliderCallback,
	void* p) {

	m_Position = std::make_shared<Tmpl8::vec2>(std::move(position));
	m_OldPosition = std::make_shared<Tmpl8::vec2>(std::move(position));
	m_Scale = std::make_shared<Tmpl8::vec2>(std::move(scale));

	m_Acceleration = std::make_shared<Tmpl8::vec2>(0.0f, 0.0f);
	m_LastTickVelocity = std::make_shared<Tmpl8::vec2>(0.0f, 0.0f);

	m_DeltaTime = 0;
	m_UseGravity = false;

	m_ColiderCallback = colliderCallback;
	m_Colider_P = p;
}

void _ColiderCallback(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {

	Physics* instance = reinterpret_cast<Physics*>(p);
	instance->PhysicsColideCallback(
		c1, 
		c2, 
		info, 
		p);
}

void Physics::InitGravity(float maxVelocity) {
	m_UseGravity = true;
	m_MaxVelocity = maxVelocity;
}

void Physics::PhysicsColideCallback(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p) {

	if (m_UseGravity && info.direction == UP) {
		SetVelocity(Tmpl8::vec2(0.0f, -m_LastTickVelocity->y * 0.8f));
	}

	if (m_ColiderCallback == nullptr) {
		return;
	}
	m_ColiderCallback(
		c1,
		c2,
		info,
		m_Colider_P);
}

void Physics::SetAABBColider() {
	auto colliderInfo = ColliderInfo(
		shared_from_this(), 
		_ColiderCallback, 
		this);
	
	auto collider = 
		std::make_shared<AABBCollider>(
			colliderInfo);

	ColiderManager::GetInstance().RegisterColider(collider);
}

void Physics::SetCircularColider() {
	auto colliderInfo = ColliderInfo(
		shared_from_this(),
		_ColiderCallback,
		this);

	auto collider = 
		std::make_shared<CircularCollider>(colliderInfo);

	ColiderManager::GetInstance().RegisterColider(collider);
}

void Physics::GetPosition(Tmpl8::vec2& out) {
	out.x = m_Position->x;
	out.y = m_Position->y;
}

void Physics::AddPosition(Tmpl8::vec2& const position) {
	m_Position->x += position.x;
	m_Position->y += position.y;
}

void Physics::SetPosition(Tmpl8::vec2& const position) {
	m_Position->x = position.x;
	m_Position->y = position.y;
}

void Physics::GetScale(Tmpl8::vec2& out) {
	out.x = m_Scale->x;
	out.y = m_Scale->y;
}

void Physics::Tick() {
	if (!m_UseGravity) {
		return;
	}

	ApplyGravity();

	Tmpl8::vec2 velocity;
	GetVelocity(velocity);

	if (velocity.y > -m_MaxVelocity) {
		SetVelocity(Tmpl8::vec2(velocity.x, -m_MaxVelocity));
		GetVelocity(velocity);
	}

	velocity.x -= velocity.x * 0.4f;

	m_DeltaTime = 1.0f / Constants::PhysicsTickInterval;

	m_OldPosition->x = m_Position->x;
	m_OldPosition->y = m_Position->y;

	m_Position->x = m_Position->x + velocity.x + m_Acceleration->x * pow(m_DeltaTime, 2);
	m_Position->y = m_Position->y + velocity.y + m_Acceleration->y * pow(m_DeltaTime, 2);

	m_Acceleration->x = 0.0f;
	m_Acceleration->y = 0.0f;

	m_LastTickVelocity->x = velocity.x;
	m_LastTickVelocity->y = velocity.y;

}

void Physics::AddVelocity(Tmpl8::vec2& const velocity) {
	m_OldPosition->x -= velocity.x;
	m_OldPosition->y -= velocity.y;
}

void Physics::SetVelocity(Tmpl8::vec2& const velocity) {
	m_OldPosition->x = m_Position->x - velocity.x;
	m_OldPosition->y = m_Position->y - velocity.y;
}

void Physics::Accelerate(Tmpl8::vec2& const acceleration) {
	m_Acceleration->x += acceleration.x;
	m_Acceleration->y += acceleration.y;
}

void Physics::ApplyGravity() {
	Accelerate(m_Gravity);
}

void Physics::GetVelocity(Tmpl8::vec2& const out) {
	out.x = m_Position->x - m_OldPosition->x;
	out.y = m_Position->y - m_OldPosition->y;
}

void Physics::GetFriction(Tmpl8::vec2& const out) {
	Tmpl8::vec2 velocity;
	GetVelocity(velocity);

	auto friction = velocity;
	friction.normalize();

	if (velocity.x == 0) {
		friction.x = 0;
	}
	if (velocity.y == 0) {
		friction.y = 0;
	}

	out = friction;
}

bool Physics::UseGravity() {
	return m_UseGravity;
}
