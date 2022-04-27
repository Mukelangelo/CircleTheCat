#include "Cat.h"
#include "Controller.h"

Cat::Cat(Board& board, sf::Vector2f loc, Controller* controller)
	: m_cat(sf::Sprite()), m_location(loc), m_board(&board), m_controller(controller) {
	m_cat.setPosition(m_location);
	m_normal.loadFromFile("def_cat.png");
	m_walking.loadFromFile("mad_cat.png");
	m_cat.setTexture(m_normal);
}

// ===================================================================================================

sf::Vector2f Cat::getLocation() {
	return m_location;
}

// ===================================================================================================

void Cat::setLocation(const sf::Vector2f& loc) {
	m_location = loc;
}

// ===================================================================================================

sf::Vector2f Cat::calculateNextTile() {
	auto index = bfs(m_board->getIndex(m_x, m_y));
	if (index == FINISH)
		m_escaped = true;
	if (index == ENCIRCLED) {
		index = nextStep(m_board->getIndex(m_x, m_y));
		if (index == FINISH)
			m_captured = true;
	}

	return m_board->getPosition(index, m_x, m_y);
}

// ===================================================================================================

void Cat::draw(sf::RenderWindow& window) const {
	window.draw(m_cat);
}

// ===================================================================================================

void Cat::jump(sf::RenderWindow& window) {
	auto dest = calculateNextTile();

	const sf::Time timerLimit = sf::seconds(0.5f);
	sf::Clock clock;
	auto factor = 0.f, speed = .01f;
	
	m_cat.setTexture(m_walking);
	while (m_location != dest) {
		if (clock.getElapsedTime() >= timerLimit)
			clock.restart();

		factor += clock.getElapsedTime().asSeconds() * speed;

		m_cat.setPosition(interpolate(m_location, dest, factor));
		m_location = m_cat.getPosition();

		m_controller->draw();
		window.display();
	}
	m_cat.setTexture(m_normal);
}

// ===================================================================================================

int Cat::getX() const {
	return m_x;
}

// ===================================================================================================

int Cat::getY() const {
	return m_y;
}

// ===================================================================================================

int Cat::bfs(int u)
{
	auto graph = m_board->buidGraph();
	std::queue<int> q;
	std::vector<bool> visited;
	visited.assign(121, false);

	q.push(u);
	visited[u] = true;
	m_board->resetDistance();
	m_board->updateCirceData(u, 0, m_board->getCircle(u));
	while (!q.empty()) {
		int val = q.front();
		q.pop();
		for (auto i = graph[val].begin(); i != graph[val].end(); i++) {
			if (!visited[*i]) {
				q.push(*i);
				visited[*i] = true;
				m_board->updateCirceData((*i), m_board->getDistance(val) + 1, m_board->getCircle(val));
			}
		}
	}
	return m_board->findShortestPath(u);
}

// ===================================================================================================

bool Cat::getEscapeStatus() {
	return m_escaped;
}

// ===================================================================================================

bool Cat::getCaptureStatus() {
	return m_captured;
}

// ===================================================================================================

int Cat::nextStep(int u) {
	auto graph = m_board->buidGraph();
	if (graph[u].size() == 0)
		return FINISH;
	return (graph[u].size() != 1) ? graph[u][1] : graph[u][0];
}

// ===================================================================================================

void Cat::resetCat() {
	m_escaped = false;
	m_captured = false;
	m_x = 5;
	m_y = 5;
	m_cat.setPosition(m_location);
}

// ===================================================================================================

void Cat::setPosition(sf::Vector2f pos, int x, int y) {
	m_cat.setPosition(pos);
	m_location = pos;
	m_x = x;
	m_y = y;
}

// ===================================================================================================

sf::Vector2f Cat::interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor) {
	if (factor > 1.f)
		factor = 1.f;

	else if (factor < 0.f)
		factor = 0.f;

	return pointA + (pointB - pointA) * factor;
}