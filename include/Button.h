#pragma once
#include <SFML/Graphics.hpp>
//#include "Resources.h"

class Button
{
public:
	Button();
	Button(const sf::Vector2f& size, const sf::String& text, const sf::Vector2f& pos);

	// check click on the button
	bool handleClick(const sf::Vector2f& location);

	void draw(sf::RenderWindow& window);

	// set color to the button by parameter or to default color
	void setColor(sf::Color color);
	void setColor();

	// get bounding rectangle of the button rectangle.
	sf::FloatRect getGlobalBounds() const;

private:
	sf::RectangleShape m_button;
	sf::Color m_color;
	sf::ConvexShape m_spare;
	sf::Text m_buttonText;
	sf::Font m_font;


	void initButton(); // set the buttons default values
};