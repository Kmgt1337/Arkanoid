#include "Ball.h"
#include <iostream>

Ball::Ball(float x, float y)
{
	shape.setPosition(x, y);
	shape.setRadius(this->ballRadius);
	shape.setOrigin(this->ballRadius, this->ballRadius);
	shape.setFillColor(sf::Color::Black);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Ball::update()
{
	std::cout << this->ballVeliocity_Y << std::endl;
	this->shape.move(veliocity);
	if (this->left() < 0)
	{
		this->veliocity.x = ballVeliocity_X;
	}
	else if (this->right() > 1200)
	{
		this->veliocity.x = -ballVeliocity_X;
	}
	if (this->top() < 0)
	{
		this->veliocity.y = ballVeliocity_Y;
	}
	if (this->bottom() > 800)
	{
		this->veliocity.y = -ballVeliocity_Y;
	}
}

float Ball::left()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Ball::right()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Ball::top()
{
	return this->shape.getPosition().y - shape.getRadius();
}

float Ball::bottom()
{
	return this->shape.getPosition().y + shape.getRadius();
}

void Ball::checkRectangle(float x, float y)
{
	if (this->ballVeliocity_Y > 0 &&
		(this->bottom() >= y && this->bottom() <= y + 20.0f) &&
		this->shape.getPosition().x >= x && this->shape.getPosition().x <= x + 100.0f)
	{
		this->veliocity.y = -ballVeliocity_Y;
	}
	else if (this->ballVeliocity_Y < 0 &&
		(this->top() <= y + 20.0f && this->top() >= y) &&
		this->shape.getPosition().x >= x && this->shape.getPosition().x <= x + 100.0f)
	{
		this->veliocity.y = -ballVeliocity_Y;
	}
}

void Ball::changeAfterHit()
{
	if (ballVeliocity_X < 0) this->veliocity.x = ballVeliocity_X;
	else					 this->veliocity.x = veliocity.x;
	
	this->veliocity.y = ballVeliocity_Y;
}

void Ball::increaseSpeed()
{
	this->ballVeliocity_X += 0.175f;
	this->ballVeliocity_Y += 0.175f;
}

bool Ball::gameOver()
{
	if (this->bottom() > 800)
	{
		return true;
	}
	return false;
}

