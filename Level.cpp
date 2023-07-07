#include "Level.h"
#include "Ball.h"

Level::Level(
	std::shared_ptr<Ball> ball) {
	
	m_Ball = ball;

	m_LevelIndex = std::make_shared<LevelIndex>(1, 1);
}

void Level::AddObject(std::shared_ptr<Object> object) {
	m_Objects.push_back(object);
}

std::list<std::shared_ptr<Object>>& const Level::GetObjects() {
	return m_Objects;
}

void Level::Reset() {
	m_Ball->Reset();
}

void Level::GetLevelIndex(LevelIndex& out) {
	out.major = m_LevelIndex->major;
	out.minor = m_LevelIndex->minor;
}
