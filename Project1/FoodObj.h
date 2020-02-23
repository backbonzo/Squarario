#pragma once
#include <SFML/Graphics.hpp>

class FoodObj {
private:
	sf::CircleShape foodBlob;
	sf::Color foodColor;
	sf::Vector2f foodXY;
	bool eaten = false;
public:
	void setFoodBlob(sf::CircleShape);
	void setfoodColor(sf::Color);
	void updatePos(sf::Vector2f );

	sf::CircleShape getFoodBlob();
	bool isEaten();

	FoodObj(sf::CircleShape, sf::Color, sf::Vector2f);
	~FoodObj() {};
};