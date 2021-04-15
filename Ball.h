#pragma once
#include <SFML\Graphics.hpp>

class Ball : public sf::Drawable
{
public:
	Ball(float x, float y);
	Ball() = delete;
	~Ball() = default;

	void update();
	void changeAfterHit();

	void checkRectangle(float x, float y);

	float left();
	float right();
	float top();
	float bottom();

	void increaseSpeed();
	bool gameOver();
	sf::CircleShape shape;

private:
	const float ballRadius{ 20.0f };
	float ballVeliocity_X{ 5.0f };
	float ballVeliocity_Y{ 5.0f };
	sf::Vector2f veliocity{ ballVeliocity_X, ballVeliocity_Y };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};
