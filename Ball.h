#pragma once
#include <SFML\Graphics.hpp>

class Ball : public sf::Drawable
{
public:
	Ball(float x, float y, float Vx, float Vy);
	Ball() = delete;
	~Ball() = default;

	void update();
	void changeAfterHitBottom();
	void changeAfterHitTop();

	void checkRectangle(float x, float y);

	float left();
	float right();
	float top();
	float bottom();

	void increaseSpeed();
	bool gameOver();
	void reset(float x, float y, float Vx, float Vy);

	void checkBallTexture(sf::Texture& ballTextureRight, sf::Texture& ballTextureLeft);
	
	sf::CircleShape shape;
	sf::Vector2f veliocity{ ballVeliocity_X, ballVeliocity_Y };

private:
	const float ballRadius{ 30.0f };
	float ballVeliocity_X{ 0.0f };
	float ballVeliocity_Y{ 0.0f };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};
