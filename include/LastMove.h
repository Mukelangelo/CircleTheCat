#pragma once

struct LastMove {
	LastMove(sf::Vector2f loc, sf::Vector2f block, int x, int y) {
		m_lastBlock = block;
		m_lastLoc = loc;
		m_x = x;
		m_y = y;
	}

	sf::Vector2f m_lastLoc;
	sf::Vector2f m_lastBlock;
	int m_x, m_y;
};