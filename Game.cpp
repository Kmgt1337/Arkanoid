#include "Game.h"
#include "Text.cpp"
#include "Textures.cpp"
#include "Menu.h"
#include "SubMenu.h"
#include <random>

void Game::initGame(std::vector<std::unique_ptr<Rectangle>>& rectangles, Rectangle& rectangle, Ball& ball, sf::RenderWindow& window, sf::RectangleShape& background, sf::Texture& backgroundTexture, sf::Texture& ballTextureRight, sf::Texture& ballTextureLeft, sf::Texture& rectanglesTexture)
{
	rectangle.setPosition(500, 700);
	rectangle.setColor(sf::Color::Green);
	rectangle.setSize(100, 20);

	window.setFramerateLimit(60);
	window.clear(sf::Color::White);

	background.setPosition(600, 400);
	background.setOrigin(600, 400);
	background.setSize({ 1200, 800 });

	background.setTexture(&backgroundTexture);
	ball.checkBallTexture(ballTextureRight, ballTextureLeft);
	for (auto& elem : rectangles)
	{
		elem->shape.setFillColor(sf::Color::Magenta);
		//elem->shape.setTexture(&rectanglesTexture);
	}
}

bool Game::isGameEnd(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball)
{
	if (rectangleGameOver(rectangles))
	{
		return true;
	}
	else if (ball.gameOver())
	{
		return true;
	}
	return false;
}

void Game::reset(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball, Rectangle& rectangle, sf::Texture& rectanglesTexture, float& speed, size_t& points)
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
}

std::vector<std::unique_ptr<Rectangle>> Game::createRectangles()
{
	std::vector<std::unique_ptr<Rectangle>> rectangles;
	for (size_t i = 0; i < 30; i++)
		rectangles.push_back(std::make_unique<Rectangle>());

	size_t x = 10;
	size_t y = 10;

	for (size_t i = 0; i < 10; i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 150;
	}
	x = 10;
	y = 90;
	for (size_t i = 10; i < 20; i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 150;
	}
	x = 10;
	y = 170;
	for (size_t i = 20; i < rectangles.size(); i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 150;
	}

	return rectangles;
}

void Game::moveRectnangle(Rectangle& rectangle)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rectangle.move(sf::Keyboard::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rectangle.move(sf::Keyboard::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		rectangle.move(sf::Keyboard::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		rectangle.move(sf::Keyboard::Down);
	}
}

void Game::checkRectangles(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball* ball, size_t& count)
{
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		size_t pom = rectangles[i]->isHit(ball->shape.getPosition().x, ball->shape.getPosition().y, ball->veliocity.x, ball->veliocity.y);
		if (pom == 1)
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHitBottom();
			ball->increaseSpeed();
			count++;
			break;
		}
		else if (pom == 2)
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHitTop();
			ball->increaseSpeed();
			count++;
			break;
		}
	}
}

size_t Game::generateCoords()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 300,700 };

	return draw(gen);
}

float Game::generateSpeed()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 1,10 };

	if (draw(gen) % 2) return -5.0f;
	else return 5.0f;
}

bool Game::rectangleGameOver(std::vector<std::unique_ptr<Rectangle>>& rectangles)
{
	if (rectangles.size() == 0) return true;
	else return false;
}

void Game::game()
{
	constexpr size_t windowWidth = 1200;
	constexpr size_t windowHeight = 800;

	std::vector<std::unique_ptr<Rectangle>> rectangles = createRectangles();

	float speed = generateSpeed();
	Ball ball(static_cast<float>(generateCoords()), 400, speed, abs(speed));

	Rectangle rectangle;
	sf::RenderWindow window{ sf::VideoMode(windowWidth, windowHeight), "Arkanoid" };
	sf::Event event, event1;

	sf::RectangleShape background;

	sf::Font font;
	font.loadFromFile("fonts/OpenSans-Regular.ttf");
	sf::Texture ballTextureRight = makeBallTextureRight();
	sf::Texture ballTextureLeft = makeBallTextureLeft();
	sf::Texture rectanglesTexture = makeRectanglesTexture();
	sf::Texture backgroundTexture = makeBackgroundTexture();

	size_t points = 0;

	Menu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	SubMenu subMenu1(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), 3, { "LATWY", "SREDNI", "TRUDNY" });
	bool menuOper = false;

	initGame(rectangles, rectangle, ball, window, background, backgroundTexture, ballTextureRight, ballTextureLeft, rectanglesTexture);

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}

			/*if (event.type == sf::Event::KeyPressed)
			{
				if (event.type == sf::Keyboard::Up)
				{
					menu.moveUp();
				}
				else if (event.type == sf::Keyboard::Down)
				{
					menu.moveDown();
				}
				if (event.type == sf::Keyboard::Return)
				{
					switch (menu.getPressedItem())
					{
					case 0:
						while (window.isOpen())
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

							if (isGameEnd(rectangles, ball))
							{
								reset(rectangles, ball, rectangle, rectanglesTexture, speed, points);
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
					case 1:
						break;
					case 2:
						return;

					}
				}*/

				/*switch (event.type)
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
							break;
						case 1:
							menuOper = true;
							switch (event.type)
							{
								case sf::Event::KeyPressed:
								switch (event.key.code)
								{
								case sf::Keyboard::Up:
									subMenu1.moveUp();
									break;
								case sf::Keyboard::Down:
									subMenu1.moveDown();
									break;

								case sf::Keyboard::Return:
									switch (subMenu1.getPressedItem())
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

											if (isGameEnd(rectangles, ball))
											{
												reset(rectangles, ball, rectangle, rectanglesTexture, speed, points);
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
										return;
									}
								}
							}
							break;
						case 2:
							return;
						}
					}
				}
			}*/

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up)		   
					menu.moveUp();
				else if (event.key.code == sf::Keyboard::Down) 
					menu.moveDown();
				else if (event.key.code == sf::Keyboard::Return)
				{
					switch (menu.getPressedItem())
					{
					case 0:
						while (true)
						{
							while (window.pollEvent(event1))
							{
								if (event1.type == sf::Event::KeyReleased)
								{
									if (event1.key.code == sf::Keyboard::Up)
										subMenu1.moveUp();
									else if (event1.key.code == sf::Keyboard::Down)
										subMenu1.moveDown();
									else if (event1.key.code == sf::Keyboard::Return)
									{
										switch (subMenu1.getPressedItem())
										{
										case 0:
											while (window.isOpen())
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

												if (isGameEnd(rectangles, ball))
												{
													reset(rectangles, ball, rectangle, rectanglesTexture, speed, points);
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
										case 1: break;
										case 2: break;
										}
									}

								}
							}
							window.clear(sf::Color::White);
							subMenu1.draw(window);
							window.display();
						}
						break;
					case 1: break;
					case 2: return;
					}
				}
			}
		}
		if (!menuOper) menu.draw(window);
		else		   subMenu1.draw(window);
		window.display();
	}
	return;
}