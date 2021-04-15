#include <random>
#include "Rectangle.h"
#include "Ball.h"

inline std::vector<std::unique_ptr<Rectangle>> createRectangles()
{
	std::vector<std::unique_ptr<Rectangle>> rectangles;
	for (size_t i = 0; i < 30; i++)
		rectangles.push_back(std::make_unique<Rectangle>());

	size_t x = 10;
	size_t y = 10;

	for (size_t i = 0; i < 10; i++)
	{
		rectangles[i]->setColor(sf::Color::Green);
		rectangles[i]->setPosition(x, y);
		x += 150;
	}
	x = 10;
	y = 50;
	for (size_t i = 10; i < 20; i++)
	{
		rectangles[i]->setColor(sf::Color::Green);
		rectangles[i]->setPosition(x, y);
		x += 150;
	}
	x = 10;
	y = 90;
	for (size_t i = 20; i < rectangles.size(); i++)
	{
		rectangles[i]->setColor(sf::Color::Green);
		rectangles[i]->setPosition(x, y);
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
		if (rectangles[i]->isHit(ball->shape.getPosition().x, ball->shape.getPosition().y))
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHit();
			ball->increaseSpeed();
			//count++;
			break;
		}
	}
}

inline size_t generateCoords()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 400,600 };

	return draw(gen);
}


