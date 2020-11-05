#pragma once
#include <SFML/Graphics.hpp>

class Wall {
private:
	sf::Vector2f wallPos;
	sf::RectangleShape top, right, bottom, left;

public:
	void render(sf::RenderWindow& window);
	Wall(sf::Vector2f, sf::Color);
};