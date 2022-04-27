#pragma once

const int INFINITE = 10000;

struct CircleData {
	CircleData(sf::CircleShape shape, int index) {
		m_shape = shape;
		m_block = false;
		m_index = index;
		m_distance = INFINITE;
		m_father = nullptr;
	}

	void resetDistance() {
		m_distance = INFINITE;
	}

	int m_index;
	sf::CircleShape m_shape;
	bool m_block;
	unsigned int m_distance;
	CircleData* m_father;
};