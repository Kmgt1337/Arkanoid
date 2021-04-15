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

	bool isHit(float x, float y);

	sf::RectangleShape shape;

private:
	const float sizeX{ 100.0f };
	const float sizeY{ 20.0f };
	sf::Vector2f size{ sizeX, sizeY };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};
