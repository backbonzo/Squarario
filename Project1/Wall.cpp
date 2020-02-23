#include "Wall.h"

Wall::Wall(sf::Vector2f wallPos, float x, float y) {
	this->wall = sf::RectangleShape(sf::Vector2f(x, y));
	this->wall.setPosition(wallPos);
	this->wall.setFillColor(sf::Color::Blue);
};

sf::RectangleShape Wall::getWall() {
	return this->wall;
}