#pragma once
#include <SFML/Graphics.hpp>

class Wall {
private:
	sf::Vector2f wallPos;
	sf::RectangleShape wall;

public:
	Wall(sf::Vector2f, float, float);

	sf::RectangleShape getWall();
};