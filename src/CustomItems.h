#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum BUTTON_STATE {IDLE = 0, HOVER = 1, PRESSED = 2};

class Button
{
public:
	Button(std::string words);
	~Button();

	const bool isPressed();
	const bool isHover();

	void Update(const sf::RenderWindow& window);
	void Render(sf::RenderTarget& target);
	void setPosition(sf::Vector2f pos);
	void setOrigin(sf::Vector2f origin);

private:
	sf::RectangleShape shape;
	sf::Color coloridle;
	sf::Color colorhover;
	sf::Color colorpress;
	sf::Text text;
	sf::Font font;
	int buttonstate;
};
