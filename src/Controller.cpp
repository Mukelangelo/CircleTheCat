#include "Controller.h"

Controller::Controller() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Circle The Cat"), m_board(Board(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Vector2f(BOARD_LOCATION, BOARD_LOCATION))), m_score(sf::Text()),
	m_font(sf::Font()), m_cat(m_board, m_board.getPosition(5, 5), this), m_level(1)
{
	srand((unsigned int)time(NULL));
	m_playing = true;
	m_restart = Button(BUTTON_SIZE, "Restart", sf::Vector2f(WINDOW_WIDTH/8, WINDOW_HEIGHT - 60));
	m_undo = Button(BUTTON_SIZE, "Undo", sf::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT - 60));
}

// ===================================================================================================

void Controller::run() {
	loadTextsAndFonts();
	restartLevel(!m_playing);
	while (m_window.isOpen()) {
		if (m_cat.getCaptureStatus())
			m_playing = false;
		if (!m_playing) {
			if (m_cat.getCaptureStatus()) {
				if (m_level == MAX_LEVEL)
					m_board.displayEndMsg(m_window, "You finished the game!");
				else 
					m_board.displayEndMsg(m_window, "Press 'Space' to go next level \nPress 'Esc' to exit the game");
				
			}
			else {
				m_board.displayEndMsg(m_window, "Press 'Space' to restart \nPress 'Esc' to exit the game");
			}
		}
		else {
			draw();
		}
		m_window.display();
		eventHandler();
	}
}

// ===================================================================================================

void Controller::eventHandler() {
	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			m_window.close();
		if (!m_playing) {
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
				m_level++;
				if (m_level == MAX_LEVEL + 1)
					m_window.close();
				restartLevel(m_cat.getEscapeStatus());
			}
		}
		else if (!m_turn) {
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:

				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				m_lastLoc = location;

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					if (m_board.handleClick(location, sf::Vector2f(float(m_cat.getX()), float(m_cat.getY())))) {
						m_clicks++;
						m_turn = !m_turn;
						continue;
					}
					if (m_restart.handleClick(location)) {
						restartLevel(true);
						m_level = MIN_LEVEL;
					}
					if (m_undo.handleClick(location)) {
						if (m_moveHistory.empty())
							break;
						undo();
					}
					break;
				}
				break;
			}
			if (m_cat.getEscapeStatus()) {
				m_playing = false;
			}
		}
	}
	if (m_turn) {
		m_moveHistory.push(LastMove(m_cat.getLocation(), m_lastLoc, m_cat.getX(), m_cat.getY()));
		m_cat.jump(m_window);
		m_turn = !m_turn;
	}
}

// ===================================================================================================

void Controller::loadTextsAndFonts(){
	m_font.loadFromFile("font.ttf");
	m_score.setFont(m_font);
	m_score.setCharacterSize(50);
	m_score.setColor(sf::Color::Black);
}

// ===================================================================================================

void Controller::restartLevel(bool lost) {
	if (lost) {
		while (!m_moveHistory.empty())
			undo();
		if (m_level != MIN_LEVEL)
			m_level--;
	}
	else {
		while (!m_moveHistory.empty())
			m_moveHistory.pop();
		m_board.restart();
		auto loc = m_board.getPosition(5, 5);
		m_cat.setLocation(loc);
		m_board.blockCircles(calulateRandomBlocks());
	}
	m_cat.resetCat();
	m_playing = true;
}

// ===================================================================================================

void Controller::draw(){
	m_window.clear(sf::Color::White);
	m_board.draw(m_window);
	m_score.setString("Clicks: " + std::to_string(m_clicks));
	m_window.draw(m_score);
	m_cat.draw(m_window);
	m_restart.draw(m_window);
	m_undo.draw(m_window);
}

// ===================================================================================================

void Controller::undo() {
	m_clicks--;
	LastMove lastMove = m_moveHistory.top();
	m_cat.setPosition(lastMove.m_lastLoc, lastMove.m_x, lastMove.m_y);
	m_board.handleClick(lastMove.m_lastBlock);
	m_moveHistory.pop();
}

unsigned int Controller::calulateRandomBlocks() {
	auto minBlock = MAX_BLOCK - (m_level * 2);
	auto maxBlock = MAX_BLOCK - (m_level - 1);
	return rand() % (maxBlock + 1 - minBlock) + minBlock;
}