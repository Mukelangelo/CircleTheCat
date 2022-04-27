#include "Button.h"

Button::Button()
{}

//=======================================================================================
Button::Button(const sf::Vector2f& size, const sf::String& text, const sf::Vector2f& pos)
    : m_button(size), m_color(126, 214, 223, 255)
{
    // initiate button by parameters
    auto location = sf::Vector2f(pos.x, pos.y + 10);
    m_button.setPosition(location);
    m_button.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    m_button.setFillColor(m_color);
    m_buttonText.setString(text);
    initButton();
}

//=======================================================================================
void Button::draw(sf::RenderWindow& window)
{
    
    m_buttonText.setFont(m_font);
    window.draw(m_button);
    window.draw(m_buttonText);
}

//=======================================================================================
bool Button::handleClick(const sf::Vector2f& location)
{
    return (m_button.getGlobalBounds().contains(location));
}

//=======================================================================================
void Button::setColor(sf::Color color)
{
    m_button.setFillColor(color);
}

//=======================================================================================
void Button::setColor()
{
    m_button.setFillColor(m_color);
}

//=======================================================================================
sf::FloatRect Button::getGlobalBounds() const
{
    return m_button.getGlobalBounds();
}

//=======================================================================================
void Button::initButton()
{
    m_button.setOutlineColor(sf::Color(96, 163, 188));
    m_button.setOutlineThickness(3);
    
    m_font.loadFromFile("font.ttf");
    m_buttonText.setFont(m_font);
    m_buttonText.Bold;
    m_buttonText.setOutlineColor(sf::Color(12, 36, 97, 255));
    m_buttonText.setOutlineThickness(2);
    m_buttonText.setCharacterSize(30);
    m_buttonText.setColor(sf::Color(29, 209, 161, 255));
    m_buttonText.setPosition(m_button.getPosition());

    auto textRect = m_buttonText.getLocalBounds();
    m_buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
}