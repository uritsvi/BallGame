#pragma once

#include <memory>
#include <list>

#include "template.h"

class Object;
class Ball;

struct LevelIndex{
	LevelIndex() = default;

	LevelIndex(
		int major, 
		int minor) {
		
		this->major = major;
		this->minor = minor;
	}

	int major;
	int minor;
};

class Level
{
public:
	Level(std::shared_ptr<Ball> ball);

	void AddObject(std::shared_ptr<Object> object);
	std::list<std::shared_ptr<Object>>& const GetObjects();

	void Reset();

	void GetLevelIndex(LevelIndex& out);
	
private:
	std::list<std::shared_ptr<Object>> m_Objects;

private:
	std::shared_ptr<Ball> m_Ball;
	std::shared_ptr<LevelIndex> m_LevelIndex;
};

