#pragma once

#include <string>
#include "Board.h"
#include "Cat.h"
#include "Button.h"
#include "LastMove.h"
#include <stack>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;
const int BOARD_LOCATION = 75;
const sf::Vector2f BUTTON_SIZE = sf::Vector2f(100, 50);
const unsigned int MAX_LEVEL = 3, MIN_LEVEL = 1,
MIN_BLOCK = 4, MAX_BLOCK = 14;

class Controller {
public:
	Controller();
	
	// Run game
	void run();

	// Draw the game
	void draw();

private:
	// Handle input from user
	void eventHandler();
	
	// Load textures and fonts 
	void loadTextsAndFonts();
	
	// Restart a level from start or begin next level
	void restartLevel(bool lost);

	// Undo last move
	void undo();

	// Calculate amount of circles to block at the start of the level
	unsigned int calulateRandomBlocks();

	Board m_board;
	Cat m_cat;
	sf::RenderWindow m_window;
	sf::Text m_score;
	sf::Font m_font;
	int m_clicks = 0;
	bool m_turn = false;
	bool m_playing;
	Button m_restart;
	Button m_undo;

	std::stack<LastMove> m_moveHistory;
	sf::Vector2f m_lastLoc;
	int m_level;
};