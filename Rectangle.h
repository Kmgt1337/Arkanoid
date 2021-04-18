#pragma once
#include <SFML\Graphics.hpp>

class Rectangle : public sf::Drawable
{
public:
	Rectangle();
	~Rectangle() = default;

	void setPosition(float x, float y);
	void setColor(sf::Color color);
	void move(sf::Keyboard::Key key);
	void setSize(float x, float y);
	int isHit(float x, float y, float Vx, float Vy);
	
	sf::RectangleShape shape;

private:
	const float sizeX{ 100.0f };
	const float sizeY{ 50.0f };
	sf::Vector2f size{ sizeX, sizeY };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};
