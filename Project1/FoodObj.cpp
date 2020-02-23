#include "FoodObj.h"

FoodObj::FoodObj(sf::CircleShape foodBlob, sf::Color foodColor, sf::Vector2f foodXY) {
	this->foodBlob = foodBlob;
	this->foodColor = foodColor;
	this->foodXY = foodXY;
	this->foodBlob.setFillColor(foodColor);
	this->updatePos(foodXY);
};


void FoodObj::updatePos(sf::Vector2f foodXY) {
	this->foodBlob.setPosition(foodXY);
}

bool FoodObj::isEaten() {
	return this->eaten;
}

sf::CircleShape FoodObj::getFoodBlob() {
	return foodBlob;
}

void FoodObj::setFoodBlob(sf::CircleShape foodBlob) {
	this->foodBlob = foodBlob;
}
void FoodObj::setfoodColor(sf::Color color) {
	this->foodColor = foodColor;
}