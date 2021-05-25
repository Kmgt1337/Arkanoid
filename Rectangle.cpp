#include "Rectangle.h"
#include "Ball.h"
#include <iostream>

Rectangle::Rectangle()
{
	this->shape.setSize(this->size);
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Rectangle::move(sf::Keyboard::Key key, float width, float height)

{
	float x = this->shape.getPosition().x;
	float y = this->shape.getPosition().y;

	switch (key)
	{
	case sf::Keyboard::Key::Left: 
		if (this->shape.getPosition().x <= 0)
		{
			this->shape.setPosition(this->shape.getPosition().x + 1, this->shape.getPosition().y);
			break;
		}
		
		x -= 10.0f; 
		break;
	
	case sf::Keyboard::Key::Right: 
		if (this->shape.getPosition().x >= width - 100)
		{
			this->shape.setPosition(this->shape.getPosition().x - 1, this->shape.getPosition().y);
			break;
		}
		
		x += 10.0f; 
		break;
	}

	this->shape.setPosition(x, y);
}

void Rectangle::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void Rectangle::setColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

int Rectangle::isHit(float x, float y, float Vx, float Vy, Ball* ball)
{
	/*if (Vx > 0 && Vy < 0)
	{
		x += 30;
		y -= 30;
	}
	else if (Vx < 0 && Vy < 0)
	{
		x -= 30;
		y -= 30;
	}
	else if (Vx > 0 && Vy > 0)
	{
		x += 30;
		y += 30;
	}
	else if (Vx < 0 && Vy > 0)
	{
		x -= 30;
		y += 30;
	}
	if (Vy < 0 && (y <= this->shape.getPosition().y + 50.0f) &&
		x >= this->shape.getPosition().x && x <= this->shape.getPosition().x + 100.0f)
	{
		return 1;
	}
	else if
		(Vy > 0 && (y <= this->shape.getPosition().y) &&
			x >= this->shape.getPosition().x && x <= this->shape.getPosition().x + 100.0f)
	{
		return 2;
	}
	return -1;*/

	const bool colids = ball->shape.getGlobalBounds().intersects(shape.getGlobalBounds());

	if (Vy < 0 && colids)
	{
		return 1;
	}
	else if (Vy > 0 && colids)
	{
		return 2;
	}
	return -1;

	//(this->shape.getPosition().y >= y - 50.0f) &&
	//	(this->shape.getPosition().x <= x + 50.0f && this->shape.getPosition().x + 150.0f >= x))
}

void Rectangle::setSize(float x, float y)
{

	this->size = { x, y };
	this->shape.setSize(size);
}

