#pragma once

#include <memory>
#include <vector>

#include "Colliders.h"
#include "template.h"

class InternalColider;

class ColiderManager
{
public:
	static ColiderManager& GetInstance();

public:
	void RegisterColider(
		std::shared_ptr<AABBCollider> collider);

	void RegisterColider(
		std::shared_ptr<CircularCollider> collider);

	void Tick();

private:
	std::vector<std::shared_ptr<Collider>> m_Coliders;
};

