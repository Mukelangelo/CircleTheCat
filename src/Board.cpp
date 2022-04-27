#include "Board.h"
#include <cmath>

Board::Board()
	: m_height(0), m_width(0), m_location(sf::Vector2f()), m_text(sf::Text()), m_font(sf::Font())
{}

// ===================================================================================================

Board::Board(int width, int height, sf::Vector2f location) 
	: m_height(height), m_width(width), m_location(location) {
	buildBoard();
	srand((int)time(NULL));
}

// ===================================================================================================

void Board::draw(sf::RenderWindow& window) const {
	for (auto itr = m_board.begin(); itr < m_board.end(); itr++) {
		for (auto ptr = itr->begin(); ptr < itr->end(); ptr++) {
			window.draw(ptr->m_shape);
		}
	}
}

// ===================================================================================================

void Board::buildBoard() {
	auto index = 0;
	auto tileWidth = (double)m_width / BOARD_SIZE, tileHeight = (double)m_height / BOARD_SIZE;
	std::vector < sf::Vector2f > teleports;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::vector<CircleData> newVec;
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			auto locationVector = (i % 2 == 0) ? sf::Vector2f(m_location.x + j * (tileWidth / 1.25), m_location.y + i * (tileHeight / 1.25))
											   : sf::Vector2f(30.0 + m_location.x + j * (tileWidth / 1.25), m_location.y + i * (tileHeight / 1.25));
			auto temp = sf::CircleShape(27);
			temp.setFillColor(sf::Color(198, 252, 3));
			temp.setPosition(locationVector);
			newVec.push_back(CircleData(temp, index));
			index++;
		}
		m_board.push_back(newVec);
	}
}

// ===================================================================================================

bool Board::handleClick(const sf::Vector2f& loc, const sf::Vector2f& catLoc) {
	for (int i = 0; i < m_board.size(); i++) {
		for (int j = 0; j < m_board[i].size(); j++) {
			if (m_board[i][j].m_shape.getGlobalBounds().contains(loc) && !m_board[i][j].m_block) {
				if (i == catLoc.x && j == catLoc.y)
					return false;
				m_board[i][j].m_shape.setFillColor(sf::Color(81, 133, 15));
				m_board[i][j].m_block = true;
				return true;
			}
		}
	}
	return false;
}

// ===================================================================================================

sf::Vector2f Board::getPosition(int i, int j) const{
	if (m_board[i][j].m_block)
		return sf::Vector2f(-1,-1);
	return m_board[i][j].m_shape.getPosition();
}

// ===================================================================================================

Graph Board::buidGraph() const {
	std::vector<Edge> edges;
	for (size_t x = 0; x < m_board.size(); x++) {
		for (size_t y = 0; y < m_board[x].size(); y++) {
			if (m_board[x][y].m_block)
				continue;
			if (x != 0 && !m_board[x - 1][y].m_block)
				edges.push_back({ m_board[x][y].m_index, m_board[x - 1][y].m_index }); 

			if(y != 0 && !m_board[x][y - 1].m_block)
				edges.push_back({ m_board[x][y].m_index, m_board[x][y - 1].m_index }); 

			if(y != 10 && !m_board[x][y + 1].m_block)
				edges.push_back({ m_board[x][y].m_index, m_board[x][y + 1].m_index }); 

			if(x != 10 && !m_board[x + 1][y].m_block)
				edges.push_back({ m_board[x][y].m_index, m_board[x + 1][y].m_index }); 

			if (x % 2 == 0) {
				if (x != 0 && y != 0 && !m_board[x - 1][y - 1].m_block)
					edges.push_back({ m_board[x][y].m_index, m_board[x - 1][y - 1].m_index });

				if (x != 10 && y != 0 && !m_board[x + 1][y - 1].m_block)
					edges.push_back({ m_board[x][y].m_index, m_board[x + 1][y - 1].m_index });
			}
			else {
				if (x != 0 && y != 10 && !m_board[x - 1][y + 1].m_block)
					edges.push_back({ m_board[x][y].m_index, m_board[x - 1][y + 1].m_index });

				if (x != 10 && y != 10 && !m_board[x + 1][y + 1].m_block)
					edges.push_back({ m_board[x][y].m_index, m_board[x + 1][y + 1].m_index });
			}
		}
	}
	return Graph(edges, 121);
}

// ===================================================================================================

sf::Vector2f Board::getPosition(int index, int& x, int& y) const {
	for (int i = 0; i < m_board.size(); i++) {
		for (int j = 0; j < m_board[i].size(); j++) {
			if (m_board[i][j].m_index == index) {
				x = i;
				y = j;
				return m_board[i][j].m_shape.getPosition();
			}
		}
	}
	return sf::Vector2f(-1, -1);
}

// ===================================================================================================

int Board::getIndex(int x, int y) const {
	return m_board[x][y].m_index;
}

// ===================================================================================================

void Board::blockCircles(unsigned int num) {
	unsigned int counter = 0;

	for (int i = 0; i < m_board.size(); i++) {
		for (int j = 0; j < m_board[i].size(); j++) {
			if (i == 5 && j == 5)
				continue;
			if (counter == num)
				return;
			if (rand() % 30 > 25) {
				m_board[i][j].m_shape.setFillColor(sf::Color(81, 133, 15));
				m_board[i][j].m_block = true;
				counter++;
			}
		}
	}
}

// ===================================================================================================

void Board::updateCirceData(int index, unsigned int distance, CircleData* father) {
	for (auto itr = m_board.begin(); itr < m_board.end(); itr++) {
		for (auto ptr = itr->begin(); ptr < itr->end(); ptr++) {
			if (ptr->m_index == index) {
				ptr->m_distance = distance;
				ptr->m_father = father;
			}
		}
	}
}

// ===================================================================================================

unsigned int Board::getDistance(int index) {
	for (auto itr = m_board.begin(); itr < m_board.end(); itr++) {
		for (auto ptr = itr->begin(); ptr < itr->end(); ptr++) {
			if (ptr->m_index == index) {
				return ptr->m_distance;
			}
		}
	}
	return 0;
}

// ===================================================================================================

int Board::findShortestPath(int dest) {
	std::vector<int> path;
	std::vector<CircleData*> m_boardEdges;

	for (int i = 0; i < m_board.size(); i++) {
		for (int j = 0; j < m_board[i].size(); j++) {
			if (i == 0 || i == BOARD_SIZE - 1 || j == 0 || j == BOARD_SIZE - 1)
				m_boardEdges.push_back(&m_board[i][j]);
		}
	}
	std::sort(m_boardEdges.begin(), m_boardEdges.end(), compareDistance);
	int i = 0;
	while (i < m_boardEdges.size() && m_boardEdges[i]->m_distance == m_boardEdges[0]->m_distance)
		i++;
	CircleData* temp = m_boardEdges[rand() % i];
	while ((*temp).m_index != dest) {
		if ((*temp).m_block)
			return -2;
		path.push_back((*temp).m_index);
		temp = (*temp).m_father;
	}
	if (path.size() == 0)
		return -1;
	return path.size() != 1 ? path[path.size() - 1] : *path.begin();
}

// ===================================================================================================

CircleData* Board::getCircle(int index){
	for (auto itr = m_board.begin(); itr < m_board.end(); itr++) {
		for (auto ptr = itr->begin(); ptr < itr->end(); ptr++) {
			if (ptr->m_index == index)
				return &(*ptr);
		}
	}
	return nullptr;
}

// ===================================================================================================

void Board::resetDistance() {
	for (auto itr = m_board.begin(); itr < m_board.end(); itr++) {
		for (auto ptr = itr->begin(); ptr < itr->end(); ptr++) {
			ptr->resetDistance();
		}
	}
}

// ===================================================================================================

void Board::displayEndMsg(sf::RenderWindow& window, const sf::String& str) {
	window.clear(sf::Color::White);
	m_font.loadFromFile("font.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(50);
	m_text.setColor(sf::Color::Black);
	m_text.setPosition(sf::Vector2f(150, 300));
	m_text.setString(str);
	window.draw(m_text);
}

// ===================================================================================================

void Board::restart() {
	m_board.clear();
	buildBoard();
}

// ===================================================================================================

bool Board::handleClick(const sf::Vector2f& loc) {
	for (auto itr = m_board.begin(); itr < m_board.end(); itr++) {
		for (auto ptr = itr->begin(); ptr < itr->end(); ptr++) {
			if (ptr->m_shape.getGlobalBounds().contains(loc)) {
				ptr->m_shape.setFillColor(sf::Color(198, 252, 3));
				ptr->m_block = false;
				return true;
			}
		}
	}
	return false;
}