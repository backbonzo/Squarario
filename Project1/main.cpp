#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include "Player.h"
#include "FoodObj.h"
#include "Wall.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>

//THIS IS INSIDE THE DEV BRANCH
//Before editing files: Make a new BRANCH with feature you are changing

void updateScore(int numScore, sf::Text& text) 
{
	text.setString(std::to_string(numScore));
}

void getPos(sf::Vector2f& pos, sf::Vector2f mapSize) {
	do
	{	pos.x = rand() % (int )mapSize.x;
		pos.y = rand() % (int ) mapSize.y;
	} while ((!(pos.x > 10 && pos.x < mapSize.x - 10) || !(pos.y > 10 && pos.y < mapSize.y - 10)));
}

void checkCollisions(std::vector<FoodObj>& foods, Player& player, sf::Vector2f foodpos, int& numScore, sf::Vector2f mapSize, bool& threadsClosed) {
	
	while (!threadsClosed)
	{
		for (auto&& food : foods)
		{
			if (player.getPlayerBlob().getGlobalBounds().intersects(food.getFoodBlob().getGlobalBounds()))
			{
				getPos(foodpos, mapSize);
				food.updatePos(foodpos);
				player.setPlayerSpeed(player.getPlayerSpeed());
				//Added maxsize as paratmeter - currently its 500
				player.setPlayerSize(sf::Vector2f(player.getPlayerSize().x + 1.0f, player.getPlayerSize().y + 1.0f), 500);
				sf::RectangleShape p = player.getPlayerBlob();
				p.setSize(player.getPlayerSize());
				player.setPlayerBlob(p);
				numScore++;
			}
		}
	}
}

void randomTexture(int result, std::string &path)
{
	switch (result)
	{
	case 0:
		path = "res/texture4.png";
		break;
	case 1:
		path = "res/texture1.png";
		break;
	case 2:
		path = "res/texture2.png";
		break;
	case 3:
		path = "res/texture3.png";
		break;
	case 4:
		path = "res/texture5.png";
		break;
	}
}

void checkFoodsToDraw(std::vector<FoodObj>& foods, std::vector<FoodObj>& foodsToDraw, sf::View& player_view, bool& threadsClosed) {

	while (!threadsClosed)
	{
		std::vector<FoodObj> temp;

		for (auto&& food : foods)
		{
			if (((food.getFoodBlob().getPosition().x < player_view.getCenter().x + 5 + player_view.getSize().x / 2) && (food.getFoodBlob().getPosition().x > player_view.getCenter().x - 5 - player_view.getSize().x / 2)) && ((food.getFoodBlob().getPosition().y < player_view.getCenter().y + 5 + player_view.getSize().y / 2) && (food.getFoodBlob().getPosition().y > player_view.getCenter().y - 5 - player_view.getSize().y / 2)))
				temp.push_back(food);
		}

		foodsToDraw = temp;
	}
}

int main() {
	srand(time(NULL));
	//window size
	int H = 1024, W = 1024;

	// creating playble area e.g "map"
	const sf::Vector2f mapSize(5000, 5000);
	// creates instance of square wall
	Wall walls(mapSize, sf::Color::Blue);

	int result = rand() % 4;
	std::cout << "rand: " << result << std::endl;
	sf::Texture texture1;
	std::string path = "";
	randomTexture(result, path);
	
	if (!texture1.loadFromFile(path))
	{
		std::cout << "Error: Could not load background picture.";
	}
	// create player instance 
	Player player(sf::Vector2f(25.0f, 25.0f) , sf::Vector2f(H/2, W/2), sf::Color::Red, texture1);

	//sf::Vector2f shapeSzie1(25, 25);
	sf::RenderWindow window(sf::VideoMode(H, W), "Squarar.io");

	//Create custom view/camera
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x - 224, window.getSize().y - 224));
	
	//Texture & Font & Sprite
	sf::Texture texture;
	if (!texture.loadFromFile("res/background.png", sf::IntRect(0, 0, 1000, 1000)))
	{
		std::cout << "Error: Could not load background picture.";
	}
	sf::Sprite spriteBG;
	texture.setRepeated(true);
	spriteBG.setTexture(texture);
	spriteBG.setTextureRect(sf::IntRect(0, 0, mapSize.x, mapSize.y));

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

	//declaring food objects and vectors
	std::vector<FoodObj> foods;
	std::vector<FoodObj> foodsToDraw;
	sf::Vector2f foodpos;
	
	for (int i = 0; i < 1000; i++)
	{
		//getPos foodpos, w, h
		getPos(foodpos, mapSize);
		FoodObj food(sf::CircleShape(10.0f), sf::Color(rand() % 255, rand() % 255, rand() % 255), foodpos);
		foods.push_back(food);
	}

	bool eaten = false;

	float movSpeed = 0.1f;

	bool threadClosed = false;

	std::thread threadCollision(checkCollisions, std::ref(foods), std::ref(player), foodpos, std::ref(numScore), mapSize, std::ref(threadClosed));
	std::thread threadVisFood(checkFoodsToDraw, std::ref(foods), std::ref(foodsToDraw), std::ref(player_view), std::ref(threadClosed));
	
	while (window.isOpen())
	{
		sf::Event evt;

		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				threadClosed = true;
				window.close();
			}
		}

		sf::Vector2f shapepos = player.getPlayerBlob().getPosition();

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
		walls.render(window);
		// draw text
		window.draw(scoreText);
		window.draw(numText);
		updateScore(numScore, numText);

			for (auto&& food: foodsToDraw)
			{
				window.draw(food.getFoodBlob());
			}

		window.draw(player.getPlayerBlob());

		window.display();
	}

	threadCollision.join();
	threadVisFood.join();

	std::cout << "====END====";
	return 0;
}