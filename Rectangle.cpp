#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle()
{
	this->shape.setFillColor(sf::Color::Black);
	this->shape.setSize(this->size);
}

void Rectangle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Rectangle::move(sf::Keyboard::Key key)

{
	float x = this->shape.getPosition().x;
	float y = this->shape.getPosition().y;

	switch (key)
	{
	case sf::Keyboard::Key::Left:  x -= 7.5f; break;
	case sf::Keyboard::Key::Right: x += 7.5f; break;
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

int Rectangle::isHit(float x, float y)
{
	if ((y <= this->shape.getPosition().y + 20.0f && y >= this->shape.getPosition().y) &&
		x >= this->shape.getPosition().x && x <= this->shape.getPosition().x + 100.0f)
	{
		return 1;
	}
	/*else if
		((this->shape.getPosition().y <= y  && this->shape.getPosition().y >= y - 20.0f) &&
		(this->shape.getPosition().x >= x && this->shape.getPosition().x <= x + 100.0f))
	{
		std::cout << "hehe" << std::endl;
		return 2;
	}*/
	return -1;
}
