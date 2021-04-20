#pragma once
#include "SFML\Graphics.hpp"
#include "Rectangle.h"
#include "Ball.h"

class Game
{
public:
	void game();

private:
	void initGame(std::vector<std::unique_ptr<Rectangle>>& rectangles, Rectangle& rectangle, Ball& ball, sf::RenderWindow& window, sf::RectangleShape& background, sf::Texture& backgroundTexture, sf::Texture& ballTextureRight, sf::Texture& ballTextureLeft, sf::Texture& rectanglesTexture);
	bool isGameEnd(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball);
	void reset(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball, Rectangle& rectangle, sf::Texture& rectanglesTexture, float& speed, size_t& points);

	std::vector<std::unique_ptr<Rectangle>> createRectangles();
	void moveRectnangle(Rectangle& rectangle);
	void checkRectangles(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball* ball, size_t& count);
	size_t generateCoords();
	float generateSpeed();
	bool rectangleGameOver(std::vector<std::unique_ptr<Rectangle>>& rectangles);
};

