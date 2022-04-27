#pragma once

#include "Board.h"
#include <queue>

const int FINISH = -1;
const int ENCIRCLED = -2;

class Controller;

class Cat {
public:
	Cat(Board& board, sf::Vector2f loc, Controller* controller);

	// Get cats location
	sf::Vector2f getLocation();

	// Set cats location
	void setLocation(const sf::Vector2f& loc);

	// Draw cat
	void draw(sf::RenderWindow& window) const;

	// Calculate next circle to jump to and jump
	void jump(sf::RenderWindow& window);

	// Calculate shortest current path and update next position
	sf::Vector2f calculateNextTile();

	// Get x/y coordinant of the cat
	int getX() const;
	int getY() const;

	// BFS algorithm to calculate current shortest path to edge
	int bfs(int u);

	// Return if the cat escaped
	bool getEscapeStatus();

	// Return if the cat is captured
	bool getCaptureStatus();

	// Reset cats data to starting settings
	void resetCat();

	// Set cats position
	void setPosition(sf::Vector2f pos, int x, int y);

private:
	// Calculate next step when the cats incircled
	int nextStep(int u);

	// Calculate move animation
	sf::Vector2f interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor);

	bool m_escaped = false;
	bool m_captured = false;

	// Cats location
	sf::Vector2f m_location;

	// Cats jpg
	sf::Sprite m_cat;

	Board* m_board;

	sf::Texture m_normal, m_walking;
	bool m_currPic = true;

	Controller* m_controller;

	int m_x = 5, m_y = 5;
};