#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

void updateScore(int numScore, sf::Text& text) {
	text.setString(std::to_string(numScore));
}


class foodObj{
	private:
		sf::CircleShape foodBlob;
		sf::Color foodColor;
		sf::Vector2f foodXY;
		bool eaten = false;
	public:
		void setFoodBlob(sf::CircleShape foodBlob) {
			this->foodBlob = foodBlob;
	}
		void setfoodColor(sf::Color color) {
			this->foodColor = foodColor;
		}

		void updatePos(sf::Vector2f foodXY) {
			this->foodBlob.setPosition(foodXY);
		}

		sf::CircleShape getFoodBlob() {
			return foodBlob;
		}

		bool isEaten() {
			return this->eaten;
		}

		foodObj(sf::CircleShape foodBlob, sf::Color foodColor, sf::Vector2f foodXY) {
			this->foodBlob = foodBlob;
			this->foodColor = foodColor;
			this->foodXY = foodXY;
			this->foodBlob.setFillColor(foodColor);
			this->updatePos(foodXY);
		};
		~foodObj(){

		};
};

							//int h -- int w
void getPos(sf::Vector2f& pos, int h, int w) {
	do
	{	pos.x = rand() % w;
		pos.y = rand() % h;
	} while ((!(pos.x > 10 && pos.x < w - 10) || !(pos.y > 10 && pos.y < w - 10)));
}

int main() {
	srand(time(NULL));

	int H = 1024, W = 1024;

	// create player instance 
	Player player(sf::Vector2f(25.0f, 25.0f) , sf::Vector2f(H/2, W/2), sf::Color::Red);

	//sf::Vector2f shapeSzie1(25, 25);
	sf::RenderWindow window(sf::VideoMode(H, W), "Squarar.io");

	//Create custom view/camera
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x - 224, window.getSize().y - 224));
	
	//Texture & Font & Sprite
	sf::Texture texture;
	if (!texture.loadFromFile("res/background.png", sf::IntRect(0, 0, 10000, 10000)))
	{
		std::cout << "Error: Could not load background picture.";
	}
	sf::Sprite spriteBG;
	texture.setRepeated(true);
	spriteBG.setTexture(texture);
	//spriteBG.setColor(sf::Color(0, 0, 0, 255));

	//Create font and load it from file!
	sf::Font font;
	if (!font.loadFromFile("res/font.ttf"))
	{
		std::cerr << "Could not load font!";
	}
	//Creating text and setting it also making empty text for score numbers;
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(35);
	scoreText.setFillColor(sf::Color::Blue);
	scoreText.setString("Score: ");

	sf::Text numText;
	int numScore = 0; //empty placeholder for score
	numText.setFont(font);
	numText.setCharacterSize(30);
	numText.setFillColor(sf::Color::Blue);
	//Setting the string empty to begin with
	numText.setString("");

	std::vector<foodObj> foods;
	sf::Vector2f foodpos;

	for (int i = 0; i < 100; i++)
	{
		//getPos foodpos, w, h
		getPos(foodpos, 2000, 2000);
		foodObj food(sf::CircleShape(10.0f), sf::Color(rand() % 255, rand() % 255, rand() % 255), foodpos);
		foods.push_back(food);
	}

	bool eaten = false;

	float movSpeed = 0.1f;
	
	while (window.isOpen())
	{
		sf::Event evt;

		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		sf::Vector2f shapepos = player.getPlayerBlob().getPosition();

		for (auto&& food : foods )
		{
			if (player.getPlayerBlob().getGlobalBounds().intersects(food.getFoodBlob().getGlobalBounds()))
			{
				eaten = true;
				//getPos foodpos, w, h
				getPos(foodpos, 2000, 2000);
				food.updatePos(foodpos);
				player.setPlayerSpeed(player.getPlayerSpeed());
				player.setPlayerSize(sf::Vector2f(player.getPlayerSize().x + 1.0f, player.getPlayerSize().y + 1.0f));
				sf::RectangleShape p = player.getPlayerBlob();
				p.setSize(player.getPlayerSize());
				player.setPlayerBlob(p);
				numScore++;
			}
		}

		//moves player of wasd keys are pressed and making h, w as border for now
		player.movePlayer(sf::Keyboard(), H, W);
		
		// we keep our view centered on the player
		player_view.setCenter(player.getPlayerPos());
		window.setView(player_view);

		//scoreText.setPosition(player_view.getViewport().width, player_view.getViewport().height);
		scoreText.setPosition(player.getPlayerPos().x - player_view.getSize().x/2, player.getPlayerPos().y - player_view.getSize().y / 2);
		numText.setPosition(player.getPlayerPos().x +125 - player_view.getSize().x / 2, player.getPlayerPos().y +5 - player_view.getSize().y / 2);

		window.clear();

		window.draw(spriteBG);

		window.draw(scoreText);
		window.draw(numText);
		updateScore(numScore, numText);

			for (auto&& food: foods)
			{
				if (!food.isEaten());
				window.draw(food.getFoodBlob());
			}

		window.draw(player.getPlayerBlob());

		window.display();

		eaten = false;

	}

	return 0;
}