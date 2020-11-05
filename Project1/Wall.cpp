#include "Wall.h"

Wall::Wall(sf::Vector2f mapSize, sf::Color color)
	: top(sf::Vector2f(mapSize.x, 2)), right(sf::Vector2f(2, mapSize.y)), bottom(sf::Vector2f(mapSize.x, 2)), left(sf::Vector2f(2, mapSize.y))
{
	//this->wall = sf::RectangleShape(sf::Vector2f(x, y));
	//this->wall.setPosition(wallPos);
	//this->wall.setFillColor(sf::Color::Blue);
	top.setPosition(sf::Vector2f(0, 0));
	right.setPosition(sf::Vector2f(mapSize.x, 0));
	bottom.setPosition(sf::Vector2f(0, mapSize.y));
	left.setPosition(sf::Vector2f(0, 0));

	top.setFillColor(color);
	right.setFillColor(color);
	bottom.setFillColor(color);
	left.setFillColor(color);

};

void Wall::render(sf::RenderWindow& window) {

	window.draw(top);
	window.draw(right);
	window.draw(bottom);
	window.draw(left);

}