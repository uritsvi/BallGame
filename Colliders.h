#pragma once

#include <memory>

#include "template.h"

class AABBCollider;
class CircularCollider;
class Physics;
class Collider;


enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE,
};

struct CollisionInfo {
	Direction direction;
};

typedef void(*OnColide)(
	Collider& c1,
	Collider& c2,
	CollisionInfo& const info,
	void* p);

struct Rect {
	Rect(
		float x, 
		float y, 
		float dx, 
		float dy
	);

	float x;
	float y;
	float dx;
	float dy;
};

struct ColliderInfo{
	ColliderInfo() = default;

	ColliderInfo(
		std::weak_ptr<Physics> physics, 
		OnColide callback, 
		void* p);

	std::weak_ptr<Physics> physics;
	OnColide callback;
	void* p;
};

class Collider {
public:
	Collider(ColliderInfo& const info);

	virtual bool AcceptCollider(Collider& collider) = 0;

	virtual bool ColideWith(AABBCollider& collider) = 0;
	virtual bool ColideWith(CircularCollider& collider) = 0;

	virtual void UpdateData() = 0;

	void GetColliderInfo(ColliderInfo& out);

private:
	std::shared_ptr<ColliderInfo> m_Info;
};

class AABBCollider : public Collider {

public:
	AABBCollider(ColliderInfo& const info);

	bool AcceptCollider(Collider& collider);

	bool ColideWith(AABBCollider& collider) override;
	bool ColideWith(CircularCollider& collider) override;

	void UpdateData() override;

	void GetRect(Rect& out);

private:
	std::shared_ptr<Rect> m_Rect;
};

class CircularCollider : public Collider {

public:
	CircularCollider(ColliderInfo& const info);

	bool AcceptCollider(Collider& collider);

	bool ColideWith(AABBCollider& collider);
	bool ColideWith(CircularCollider& collider);

	void UpdateData() override;

	float GetRadius();
	void GetCenter(Tmpl8::vec2& out);

private:
	float m_Radius;
	std::shared_ptr<Tmpl8::vec2> m_Center;

};