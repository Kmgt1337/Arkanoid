#ifndef GAME_H
#define GAME_H
#include "SFML\Graphics.hpp"
#include "Rectangle.h"
#include "Ball.h"
#include "GameSound.h"

class Game
{
public:
	void game();

private:
	void initGame(std::vector<std::unique_ptr<Rectangle>>& rectangles, Rectangle& rectangle, Ball& ball, Ball& ball1, sf::RenderWindow& window, sf::RectangleShape& background, sf::Texture& backgroundTexture, sf::Texture& ballTextureRight, sf::Texture& ballTextureLeft, sf::Texture& rectanglesTexture);
	bool isGameEnd(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball, float height);
	void reset(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball, Rectangle& rectangle, sf::Texture& rectanglesTexture, float& speed, size_t& points);

	std::vector<std::unique_ptr<Rectangle>> createRectangles();
	void moveRectnangle(Rectangle& rectangle, float width, float height);
	void checkRectangles(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball* ball, GameSound& sounds, size_t& count);
	float generateCoords();
	float generateSpeedEasy();
	float generateSpeedMedium();
	float generateSpeedHard();
	bool rectangleGameOver(std::vector<std::unique_ptr<Rectangle>>& rectangles);

	void ballsHit(Ball& ball1, Ball& ball2);

	void drawEverything(sf::RenderWindow& window, Rectangle rectangle, Ball ball, Ball ball1, sf::Text text, std::vector<std::unique_ptr<Rectangle>>& rectangles, sf::RectangleShape texture);
	void setMessage(std::string message, size_t points, const float windowWidth, const float windowHeight, sf::Text& text1);

	void lostGameScreen();
	void winGameScreen();

	sf::Text showWinMessage(std::string message, size_t points, sf::Font font);
};

#endif

