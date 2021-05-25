#include "Game.h"
#include "Text.cpp"
#include "Textures.cpp"
#include "Menu.h"
#include "SubMenu.h"
#include "GameSound.h"
#include <random>

void Game::initGame(std::vector<std::unique_ptr<Rectangle>>& rectangles, Rectangle& rectangle, Ball& ball, Ball& ball1, sf::RenderWindow& window, sf::RectangleShape& background, sf::Texture& backgroundTexture, sf::Texture& ballTextureRight, sf::Texture& ballTextureLeft, sf::Texture& rectanglesTexture)
{
	float cords = generateCoords();
	ball.shape.setPosition({cords, 844 });
	ball1.shape.setPosition({ cords, 844 });

	rectangle.setPosition(ball.shape.getPosition().x, 850);
	rectangle.setColor(sf::Color::Blue);
	rectangle.setSize(100, 20);

	window.setFramerateLimit(60);
	window.clear(sf::Color::White);

	background.setPosition(600, 400);
	background.setOrigin(600, 400);
	background.setSize({ 1800, 950 });
	background.setTexture(&backgroundTexture);

	ball.checkBallTexture(ballTextureRight, ballTextureLeft);
	for (auto& elem : rectangles)
	{
		elem->shape.setFillColor(sf::Color::White);
		elem->shape.setTexture(&rectanglesTexture);
	}
}

bool Game::isGameEnd(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball, float height)
{
	if (ball.gameOver(height))
	{
		return true;
	}
	return false;
}

void Game::reset(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball& ball, Rectangle& rectangle, sf::Texture& rectanglesTexture, float& speed, size_t& points)
{
	speed = generateSpeedEasy();
	ball.reset(static_cast<float>(generateCoords()), 400, speed, abs(speed));
	rectangles.clear();
	rectangles = createRectangles();
	points = 0;
	rectangle.setPosition(500, 700);
	for (auto& elem : rectangles)
	{
		elem->shape.setFillColor(sf::Color::White);
		//elem->shape.setTexture(&rectanglesTexture);
	}
}

std::vector<std::unique_ptr<Rectangle>> Game::createRectangles()
{
	std::vector<std::unique_ptr<Rectangle>> rectangles;
	for (size_t i = 0; i < 51; i++)
		rectangles.push_back(std::make_unique<Rectangle>());

	size_t x = 0;
	size_t y = 10;

	for (size_t i = 0; i < 17; i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 105;
	}
	x = 0;
	y = 90;
	for (size_t i = 17; i < 34; i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 105;
	}
	x = 0;
	y = 170;
	for (size_t i = 34; i < rectangles.size(); i++)
	{
		rectangles[i]->setPosition(static_cast<float>(x), static_cast<float>(y));
		x += 105;
	}

	return rectangles;
}

void Game::moveRectnangle(Rectangle& rectangle, float width, float height)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rectangle.move(sf::Keyboard::Left, width, height);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rectangle.move(sf::Keyboard::Right, width, height);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		rectangle.move(sf::Keyboard::Up, width, height);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		rectangle.move(sf::Keyboard::Down, width, height);
	}
}

void Game::checkRectangles(std::vector<std::unique_ptr<Rectangle>>& rectangles, Ball* ball, GameSound& sounds, size_t& count)
{
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		size_t pom = rectangles[i]->isHit(ball->shape.getPosition().x, ball->shape.getPosition().y, ball->veliocity.x, ball->veliocity.y, ball);
		if (pom == 1)
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHitBottom();
			ball->increaseSpeed();
			sounds.playSound();
			count++;
			break;
		}
		else if (pom == 2)
		{
			rectangles.erase(rectangles.begin() + i);
			ball->changeAfterHitTop();
			ball->increaseSpeed();
			sounds.playSound();
			count++;
			break;
		}
	}
}

float Game::generateCoords()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_real_distribution<float> draw{ 200,1600 };

	return draw(gen);
}

float Game::generateSpeedEasy()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 1,10 };

	if (draw(gen) % 2) return -7.0f;
	else return 7.0f;
}

float Game::generateSpeedMedium()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 1,10 };

	if (draw(gen) % 2) return -8.0f;
	else return 8.0f;

}

float Game::generateSpeedHard()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 1,10 };

	if (draw(gen) % 2) return -9.5f;
	else return 9.5f;
}

bool Game::rectangleGameOver(std::vector<std::unique_ptr<Rectangle>>& rectangles)
{
	if (rectangles.size() == 0) return true;
	else return false;
}

sf::Text Game::showWinMessage(std::string message, size_t points, sf::Font font)
{
	message += std::to_string(points);
	sf::Text text(message, font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(10, 750);

	return text;
}

void Game::drawEverything(sf::RenderWindow& window, Rectangle rectangle, Ball ball, Ball ball1, sf::Text text, std::vector<std::unique_ptr<Rectangle>>& rectangles, sf::RectangleShape texture)
{
	window.clear();
	window.draw(texture);
	for (auto& elem : rectangles)
	{
		window.draw(*elem);
	}
	window.draw(text);
	window.draw(rectangle);
	window.draw(ball);
	window.draw(ball1);
	window.display();

}

void Game::setMessage(std::string message, size_t points, const float windowWidth, const float windowHeight, sf::Text& text1)
{
	message += std::to_string(points);

	text1.setString(message);
	text1.setFillColor(sf::Color::White);
	text1.setCharacterSize(65);
	text1.setPosition(windowWidth / 2 - 300, windowHeight / 2);
}

void Game::ballsHit(Ball& ball1, Ball& ball2)
{
	const bool colids = ball1.shape.getGlobalBounds().intersects(ball2.shape.getGlobalBounds());

	if (colids)
	{
		ball1.veliocity.y *= -1;
		ball2.veliocity.y *= -1;
	}
}

void Game::game()
{
	constexpr float windowWidth = 1800.0f;
	constexpr float windowHeight = 950.0f;

	std::vector<std::unique_ptr<Rectangle>> rectangles = createRectangles();

	float speed = generateSpeedEasy();
	Ball ball(static_cast<float>(generateCoords()), 250, speed, abs(speed) - 1.0f);
	Ball ball1(static_cast<float>(generateCoords()), 250, -speed, abs(speed) - 1.0f);

	Rectangle rectangle;
	sf::RenderWindow window{ sf::VideoMode(static_cast<size_t>(windowWidth), static_cast<size_t>(windowHeight)), "Arkanoid"};
	sf::Event event, event1, event2;

	sf::RectangleShape background, backgroundWin, backgroundLose, backgroundPause;

	sf::Font font, font1;
	font.loadFromFile("fonts/Bahamas.ttf");
	font1.loadFromFile("fonts/BahamasBold.ttf");
	sf::Texture ballTextureRight = makeBallTextureRight();
	sf::Texture ballTextureLeft = makeBallTextureLeft();
	sf::Texture rectanglesTexture = makeRectanglesTexture();
	sf::Texture backgroundTexture = makeBackgroundTexture();

	sf::Texture backgroundLoseTexture = makeBackgroundLoseTexture();
	sf::Texture backgroundWinTexture = makeBackgroundWinTexture();
	sf::Texture backgroundPauseTexture = makeBackgroundPauseTexture();

	backgroundWin.setTexture(&backgroundWinTexture);
	backgroundLose.setTexture(&backgroundLoseTexture);
	backgroundPause.setTexture(&backgroundPauseTexture);

	backgroundWin.setPosition(600, 400);
	backgroundWin.setOrigin(600, 400);
	backgroundWin.setSize({ 1800, 950 });
	
	backgroundLose.setPosition(600, 400);
	backgroundLose.setOrigin(600, 400);
	backgroundLose.setSize({ 1800, 950 });
	
	backgroundPause.setPosition(600, 400);
	backgroundPause.setOrigin(600, 400);
	backgroundPause.setSize({ 1800, 950 });

	size_t points = 0;

	SubMenu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), { "ZAGRAJ", "OPCJE", "WYJDZ" });
	SubMenu subMenu1(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), { "LATWY", "SREDNI", "TRUDNY", "WROC" });
	bool menuOper = false;
	bool gameOper = false;

	sf::Clock clock;
	std::string message = "PUNKTY = ";
	std::string winMessage = "WYGRALES";
	std::string loseMessage = "PRZEGRALES";

	sf::Text text, text1;
	text.setFont(font);
	text1.setFont(font);

	GameSound sounds;
	sounds.addSound("sounds/1.wav");
	sounds.addSound("sounds/2.wav");
	sounds.addSound("sounds/3.wav");
	sounds.addSound("sounds/4.wav");
	sounds.addSound("sounds/5.wav");

	while (window.isOpen())
	{
		menuOper = false;
		gameOper = false;
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
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
						while (!menuOper)
						{
							while (window.pollEvent(event1))
							{
								if (event1.type == sf::Event::Closed)
								{
									window.close();
									return;
								}
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
											clock.restart();
											initGame(rectangles, rectangle, ball, ball1, window, background, backgroundTexture, ballTextureRight, ballTextureLeft, rectanglesTexture);
											speed = generateSpeedEasy();
											ball.setSpeed(speed, abs(speed) - 1.0f);
											ball1.setSpeed(speed, abs(speed) - 2.0f);
											gameOper = true;
											break;
										case 1: 
											clock.restart();
											initGame(rectangles, rectangle, ball, ball1, window, background, backgroundTexture, ballTextureRight, ballTextureLeft, rectanglesTexture);
											speed = generateSpeedMedium();
											ball.setSpeed(speed, abs(speed) - 1.0f); 
											ball1.setSpeed(speed, abs(speed) - 2.0f);
											gameOper = true;
											break;
										case 2: 
											clock.restart();
											initGame(rectangles, rectangle, ball, ball1, window, background, backgroundTexture, ballTextureRight, ballTextureLeft, rectanglesTexture);
											speed = generateSpeedHard();
											ball.setSpeed(speed, abs(speed) - 1.0f); 
											ball1.setSpeed(speed, abs(speed) - 2.0f);
											gameOper = true;
											break;
										case 3: menuOper = true; break;
										}
									}

								}
							}
							while (gameOper)
							{
								while (window.pollEvent(event1))
								{
									if (event1.type == sf::Event::Closed)
									{
										window.close();
										return;
									}
									else if (event1.type == sf::Event::KeyPressed)
									{
										if (event1.key.code == sf::Keyboard::Escape)
										{
											window.close();
											return;
										}
									}
									else if (event1.type == sf::Event::KeyReleased)
									{
										if (event1.key.code == sf::Keyboard::P)
										{
											bool pom = true;
											while (pom)
											{
												while (window.pollEvent(event2))
												{
													if (event2.type == sf::Event::Closed)
													{
														window.close();
														return;
													}
													else if (event2.type == sf::Event::KeyReleased)
													{
														if (event2.key.code == sf::Keyboard::P)
														{
															pom = false;
														}
													}
												}
												drawEverything(window, rectangle, ball, ball1, text1, rectangles, backgroundLose);
											}
										}
									}
								}
								window.clear(sf::Color::Black);
								moveRectnangle(rectangle, windowWidth, windowHeight);
								checkRectangles(rectangles, &ball, sounds, points);
								checkRectangles(rectangles, &ball1, sounds, points);
								//if(clock.getElapsedTime() > sf::seconds(2)) ballsHit(ball, ball1);

								ball.checkRectangle(rectangle.shape.getPosition().x, rectangle.shape.getPosition().y);
								ball.update(windowHeight, windowWidth);
								ball.checkBallTexture(ballTextureRight, ballTextureLeft);

								ball1.checkRectangle(rectangle.shape.getPosition().x, rectangle.shape.getPosition().y);
								ball1.update(windowHeight, windowWidth);
								ball1.checkBallTexture(ballTextureRight, ballTextureLeft);

								if (isGameEnd(rectangles, ball, windowHeight))
								{
									bool pomEnd = true;
									clock.restart();
									while (pomEnd)
									{
										while (window.pollEvent(event2))
										{
											if (event2.type == sf::Event::Closed)
											{
												window.close();
												return;
											}
											else if (event2.type == sf::Event::KeyReleased)
											{
												if (event2.key.code == sf::Keyboard::Return)
												{
													pomEnd = false;
												}
											}
										}
										setMessage("PRZEGRALES\nLICZBA PUNKTOW - ", points, windowWidth, windowHeight, text1);
										drawEverything(window, rectangle, ball, ball1, text1, rectangles, backgroundLose);
									}
									reset(rectangles, ball, rectangle, rectanglesTexture, speed, points);
									menuOper = true;									
									break;
								}
								if (isGameEnd(rectangles, ball1, windowHeight))
								{
									bool pomEnd = true;
									clock.restart();
									while (pomEnd)
									{
										while (window.pollEvent(event2))
										{
											if (event2.type == sf::Event::Closed)
											{
												window.close();
												return;
											}
											else if (event2.type == sf::Event::KeyReleased)
											{
												if (event2.key.code == sf::Keyboard::Return)
												{
													pomEnd = false;
												}
											}
										}
										setMessage("PRZEGRALES\nLICZBA PUNKTOW - ", points, windowWidth, windowHeight, text1);
										drawEverything(window, rectangle, ball, ball1, text1, rectangles, backgroundLose);
									}
									reset(rectangles, ball, rectangle, rectanglesTexture, speed, points);
									menuOper = true;
									break;
								}
								if (!rectangles.size())
								{
									clock.restart();
									while (clock.getElapsedTime() < sf::seconds(10))
									{
										setMessage("WYGRALES\nLICZBA PUNKTOW - ", points, windowWidth, windowHeight, text1);
										drawEverything(window, rectangle, ball, ball1, text1, rectangles, backgroundLose);
									}
									reset(rectangles, ball, rectangle, rectanglesTexture, speed, points);
									reset(rectangles, ball1, rectangle, rectanglesTexture, speed, points);
									menuOper = true;
									break;
								}

								message.clear();
								message = "PUNKTY: ";
								message += std::to_string(points);
								text.setString(message);
								text.setFillColor(sf::Color::White);
								text.setCharacterSize(40);
								text.setPosition(10, windowHeight - 60);

								window.draw(background);
								for (auto& elem : rectangles)
								{
									window.draw(*elem);
								}
								window.draw(text);
								window.draw(rectangle);
								window.draw(ball);
								window.draw(ball1);
								window.display();
							}

							if (menuOper) break;
							window.clear(sf::Color::Black);
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
		menu.draw(window);
		window.display();
	}
	return;
}