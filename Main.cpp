#include "Ball.h"
#include "Rectangle.h"
#include "someFunctions.cpp"
#include "Text.cpp"
#include "Textures.cpp"
#include "Menu.h"

int main(int argc, char* argv[])
{
	constexpr size_t windowWidth = 1200;
	constexpr size_t windowHeight = 800;
	constexpr float ballSize = 30.0f;

	std::vector<std::unique_ptr<Rectangle>> rectangles = createRectangles();
	
	float speed = generateSpeed();
	Ball ball(static_cast<float>(generateCoords()), 400, speed, abs(speed));

	Rectangle rectangle;
	rectangle.setPosition(500, 700);
	rectangle.setColor(sf::Color::Black);
	rectangle.setSize(100, 20);

	sf::RenderWindow window{ sf::VideoMode(windowWidth, windowHeight), argv[0] };
	window.setFramerateLimit(60);
	window.clear(sf::Color::White);
	
	sf::Event event;

	sf::RectangleShape background;
	background.setPosition(600, 400);
	background.setOrigin(600, 400);
	background.setSize({ 1200, 800 });

	sf::Font font;
	font.loadFromFile("fonts/OpenSans-Regular.ttf");
	
	sf::Texture ballTextureRight = makeBallTextureRight();
	sf::Texture ballTextureLeft = makeBallTextureLeft();
	sf::Texture rectanglesTexture = makeRectanglesTexture();
	sf::Texture backgroundTexture = makeBackgroundTexture();	

	background.setTexture(&backgroundTexture);
	ball.checkBallTexture(ballTextureRight, ballTextureLeft);
	for (auto& elem : rectangles)
	{
		elem->shape.setTexture(&rectanglesTexture);
	}

	size_t points = 0;

	Menu menu(window.getSize().x, window.getSize().y);

	while (true)
	{
		window.clear(sf::Color::White);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}

			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;
				case sf::Keyboard::Down:
					menu.moveDown();
					break;

				case sf::Keyboard::Return:

					switch (menu.getPressedItem())
					{
					case 0:
						while (true)
						{
							window.clear(sf::Color::White);
							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
								{
									window.close();
									break;
								}
							}
							moveRectnangle(rectangle);
							checkRectangles(rectangles, &ball, points);

							ball.checkRectangle(rectangle.shape.getPosition().x, rectangle.shape.getPosition().y);
							ball.update();
							ball.checkBallTexture(ballTextureRight, ballTextureLeft);
							if (ball.gameOver())
							{
								speed = generateSpeed();
								ball.reset(static_cast<float>(generateCoords()), 400, speed, abs(speed));
								rectangles.clear();
								rectangles = createRectangles();
								points = 0;
								rectangle.setPosition(500, 700);
								for (auto& elem : rectangles)
								{
									elem->shape.setTexture(&rectanglesTexture);
								}
								break;
							}
							if (rectangleGameOver(rectangles))
							{
								speed = generateSpeed();
								ball.reset(static_cast<float>(generateCoords()), 400, speed, abs(speed));
								rectangles.clear();
								rectangles = createRectangles();
								points = 0;
								rectangle.setPosition(500, 700);
								for (auto& elem : rectangles)
								{
									elem->shape.setTexture(&rectanglesTexture);
								}
								break;
							}

							std::string message = "KREMUWKI = ";
							message += std::to_string(points);

							sf::Text text(message, font);
							text.setFillColor(sf::Color::White);
							text.setCharacterSize(30);
							text.setFillColor(sf::Color::Black);
							text.setPosition(10, 750);

							window.draw(background);
							for (auto& elem : rectangles)
							{
								window.draw(*elem);
							}
							window.draw(text);
							window.draw(rectangle);
							window.draw(ball);
							window.display();
						}
						break;
					case 1:
						break;
					case 2:
						return 0;
					}
				}
			}
		}
		menu.draw(window);
		window.display();
	}

	return 0;
}