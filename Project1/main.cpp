#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include "Player.h"
#include "FoodObj.h"
#include "Wall.h"
#include <iostream>
#include <vector>
#include <string>

//THIS IS INSIDE THE DEV BRANCH
//Before editing files: Make a new BRANCH with feature you are changing

void updateScore(int numScore, sf::Text& text) 
{
	text.setString(std::to_string(numScore));
}
							//int h -- int w
void getPos(sf::Vector2f& pos, int h, int w) {
	do
	{	pos.x = rand() % w;
		pos.y = rand() % h;
	} while ((!(pos.x > 10 && pos.x < w - 10) || !(pos.y > 10 && pos.y < w - 10)));
}

int main() {
	srand(time(NULL));

	// creating input for playble area
	const sf::Vector2f mapSize(5000, 5000);

	// creatinig walls to outline blocked area
	Wall topWalls(sf::Vector2f(0, 0), mapSize.x, 2);
	Wall bottomWalls(sf::Vector2f(0, mapSize.y), mapSize.x, 2);
	Wall leftWalls(sf::Vector2f(0, 0), 2, mapSize.y);
	Wall rightWalls(sf::Vector2f(mapSize.x, 0), 2, mapSize.y);

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

	std::vector<FoodObj> foods;
	sf::Text numText;
	int numScore = 0; //empty placeholder for score
	numText.setFont(font);
	numText.setCharacterSize(30);
	numText.setFillColor(sf::Color::Blue);
	//Setting the string empty to begin with
	numText.setString("");
	sf::Vector2f foodpos;

	for (int i = 0; i < 100; i++)
	{
		//getPos foodpos, w, h
		getPos(foodpos, 2000, 2000);
		FoodObj food(sf::CircleShape(10.0f), sf::Color(rand() % 255, rand() % 255, rand() % 255), foodpos);
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
				getPos(foodpos, H, W);
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
		player.movePlayer(sf::Keyboard(), mapSize.x, mapSize.y);
		
		// we keep our view centered on the player
		player_view.setCenter(player.getPlayerPos().x + player.getPlayerSize().x/2, player.getPlayerPos().y + player.getPlayerSize().y / 2);
		window.setView(player_view);
		scoreText.setPosition(player_view.getCenter().x - player_view.getSize().x/2, player_view.getCenter().y - player_view.getSize().y / 2);
		numText.setPosition(player_view.getCenter().x + 125 - player_view.getSize().x / 2 , player_view.getCenter().y + 5 - player_view.getSize().y / 2 );

		window.clear();
		//draw backgrounds
		window.draw(spriteBG);

		// draws walls
		window.draw(topWalls.getWall());
		window.draw(bottomWalls.getWall());
		window.draw(leftWalls.getWall());
		window.draw(rightWalls.getWall());
		// draw text
		window.draw(scoreText);
		window.draw(numText);
		updateScore(numScore, numText);

			for (auto&& food: foods)
			{
				if (!food.isEaten())
				window.draw(food.getFoodBlob());
			}

		window.draw(player.getPlayerBlob());

		window.display();
	}

	return 0;
}