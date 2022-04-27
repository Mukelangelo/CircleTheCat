#pragma once

#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <set>
#include "Graph.h"
#include "CircleData.h"

class Board {
public:
	Board();

	Board(int width, int height, sf::Vector2f location);

	// Draw objects into the window
	void draw(sf::RenderWindow& window) const;

	// Handle clicks on objects on the board
	bool handleClick(const sf::Vector2f& loc, const sf::Vector2f& catLoc);
	bool handleClick(const sf::Vector2f& loc);

	// Get position of an object from the data base
	sf::Vector2f getPosition(int i, int j) const;
	sf::Vector2f getPosition(int index, int& x, int& y) const;

	// Get index of a circle
	int getIndex(int x, int y) const;

	// Build the graph from the game board
	Graph buidGraph() const;

	// Block randomly an amount of circles
	void blockCircles(unsigned int num);

	// Update data of a circle on the board
	void updateCirceData(int index, unsigned int distance, CircleData* father);

	// Get the distance from a circle on the board
	unsigned int getDistance(int index);

	// Find the shortest path from cats position to the edge given
	int findShortestPath(int dest);

	// Get pointer to a circle object
	CircleData* getCircle(int index);

	// Reset the distances of each circle on the board
	void resetDistance();

	// Display a massage when game is stopped because of win/lose
	void displayEndMsg(sf::RenderWindow& window, const sf::String& str);

	// Restart the board and its objects to starting settings
	void restart();

private:
	// Build the board from Circle shapes
	void buildBoard();

	// Board data
	std::vector<std::vector<CircleData>> m_board;

	// location of the board on the screen
	sf::Vector2f m_location;

	// sizes of the board
	int m_height, m_width;

	const int BOARD_SIZE = 11;

	sf::Text m_text;
	sf::Font m_font;
};

// Compare distances between two circles
inline bool compareDistance(CircleData* c1, CircleData* c2){
	return (*c1).m_distance < (*c2).m_distance;
}