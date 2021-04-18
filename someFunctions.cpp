#include <random>
#include "Rectangle.h"
#include "Ball.h"
#include <iostream>

inline std::vector<std::unique_ptr<Rectangle>> createRectangles()
{
	std::vector<std::unique_ptr<Rectangle>> rectangles;
	for (size_t i = 0; i < 30; i++)
		rectangles.push_back(std::make_unique<Rectangle>());

	size_t x = 10;
	size_t y = 10;

	for (size_t i = 0; i < 10; i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 150;
	}
	x = 10;
	y = 90;
	for (size_t i = 10; i < 20; i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 150;
	}
	x = 10;
	y = 170;
	for (size_t i = 20; i < rectangles.size(); i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 150;
	}

	return rectangles;
}

inline void moveRectnangle(Rectangle& rectangle)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rectangle.move(sf::Keyboard::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rectangle.move(sf::Keyboard::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		rectangle.move(sf::Keyboard::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		rectangle.move(sf::Keyboard::Down);
	}
}

inline void checkRectangles(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball* ball, size_t& count)
{
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		size_t pom = rectangles[i]->isHit(ball->shape.getPosition().x, ball->shape.getPosition().y, ball->veliocity.x, ball->veliocity.y);
		if (pom == 1)
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHitBottom();
			ball->increaseSpeed();
			count++;
			break;
		}
		else if (pom == 2)
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHitTop();
			ball->increaseSpeed();
			count++;
			break;
		}
	}
}

inline size_t generateCoords()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 300,700 };

	return draw(gen);
}

inline float generateSpeed()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 1,10 };

	if (draw(gen) % 2) return -5.0f;
	else return 5.0f;
}

inline bool rectangleGameOver(std::vector<std::unique_ptr<Rectangle>>& rectangles)
{
	if (rectangles.size() == 0) return true;
	else return false;
}

inline void game()
{

}


