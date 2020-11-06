#pragma once
#include <SFML/Graphics.hpp>

class Player{
	private:
		sf::Vector2f playerSize;
		sf::Color playerColor;
		sf::Vector2f playerXY;
		sf::RectangleShape playerBlob;
		float playerSpeed;
	public:
		Player(sf::Vector2f, sf::Vector2f, sf::Color, sf::Texture &tex);
		void setPlayerSize(sf::Vector2f, float maxSize);
		void setPlayerColor(sf::Color);
		void setPlayerXY(sf::Vector2f);
		void setPlayerBlob(sf::RectangleShape);
		void setPlayerSpeed(float);

		sf::Vector2f getPlayerPos();
		sf::Vector2f getPlayerSize();
		sf::Color getPlayerColor();
		sf::Vector2f getPlayerXY();
		sf::RectangleShape getPlayerBlob();
		
		float getPlayerSpeed();
		void movePlayer(sf::Keyboard , int, int);
};