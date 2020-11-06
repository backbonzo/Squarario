#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f playerSize , sf::Vector2f playerXY, sf::Color playerColor, sf::Texture &tex) {
	this->playerSize = playerSize;
	this->playerXY = playerXY;
	this->playerColor = playerColor;
	this->playerSpeed = 0.2f;

	this->playerBlob = sf::RectangleShape(playerSize);
	//this->playerBlob.setFillColor(playerColor);
	//
	this->playerBlob.setTexture(&tex, false);
	this->playerBlob.setPosition(playerXY);
};

void Player::setPlayerBlob(sf::RectangleShape playerBlob) {
	this->playerBlob = playerBlob;
}

void Player::setPlayerSpeed(float playerSpeed) {
	this->playerSpeed = playerSpeed;
}

void Player::setPlayerSize(sf::Vector2f playerSize, float maxSize) {
	//This checks if the playersize is LESS than 800(temporary size) if it is = set playersize to size
	if (this->getPlayerSize().x < maxSize && this->getPlayerSize().y < maxSize)
	{
		std::cout << "Player Size X:" << this->getPlayerSize().x << " Y:" << this->getPlayerSize().y << std::endl;
		this->playerSize = playerSize;
	}
}

float Player::getPlayerSpeed() {
	return this->playerSpeed;
}

sf::Color Player::getPlayerColor() {
	return this->playerColor;
}

sf::RectangleShape Player::getPlayerBlob() {
	return this->playerBlob;
}

sf::Vector2f Player::getPlayerXY() {
	return this->playerXY;
}

sf::Vector2f Player::getPlayerSize() {
	return this->playerSize;
}

sf::Vector2f Player::getPlayerPos() {
	return sf::Vector2f(this->playerBlob.getPosition().x, this->playerBlob.getPosition().y);
}

void Player::movePlayer(sf::Keyboard key, int H, int W) {
	// get the instance of the player
	sf::RectangleShape player = this->getPlayerBlob();

	if (key.isKeyPressed(sf::Keyboard::LShift))
	{
		this->playerSpeed = 10.f;
	}
	
	if (key.isKeyPressed(sf::Keyboard::A))
	{
		if (this->playerBlob.getPosition().x > 0)
			player.move(-(this->playerSpeed), 0.0f);
	}
	
	if (key.isKeyPressed(sf::Keyboard::D))
	{
		if (this->playerBlob.getPosition().x + this->playerBlob.getSize().x < H)
			player.move(this->playerSpeed, 0.0f);
	}
	
	if (key.isKeyPressed(sf::Keyboard::W))
	{
		if (this->playerBlob.getPosition().y > 0)
			player.move(0.00f, -this->playerSpeed);
	}
	
	if (key.isKeyPressed(sf::Keyboard::S))
	{
		if (this->playerBlob.getPosition().y + this->playerBlob.getSize().y < W)
			player.move(0.00f, this->playerSpeed);
	}
	// update player's instance
	this->setPlayerBlob(player);
}