#include "Ball.h"
#include <iostream>

Ball::Ball(float x, float y, float Vx, float Vy)
{
	shape.setPosition(x, y);
	shape.setRadius(this->ballRadius);
	shape.setOrigin(this->ballRadius, this->ballRadius);
	this->ballVeliocity_X = Vx;
	this->ballVeliocity_Y = Vy;
	this->veliocity = { ballVeliocity_X, ballVeliocity_Y };
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Ball::update()
{
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
	   (this->bottom() >= y && this->bottom() <= y + 30.0f) &&
		this->shape.getPosition().x >= x && this->shape.getPosition().x <= x + 130.0f)
	{
		this->veliocity.y = -ballVeliocity_Y;
	}
	else if (this->ballVeliocity_Y < 0 &&
			(this->top() <= y + 30.0f && this->top() >= y) &&
			this->shape.getPosition().x >= x && this->shape.getPosition().x <= x + 130.0f)
	{
		this->veliocity.y = -ballVeliocity_Y;
	}
}

void Ball::changeAfterHitBottom()
{
	if (ballVeliocity_X < 0) this->veliocity.x = ballVeliocity_X;
	else					 this->veliocity.x = veliocity.x;
	
	this->veliocity.y = ballVeliocity_Y;
}

void Ball::changeAfterHitTop()
{
	if (ballVeliocity_X > 0) this->veliocity.x = veliocity.x;
	else					 this->veliocity.x = -ballVeliocity_X;

	this->veliocity.y = -ballVeliocity_Y;
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

