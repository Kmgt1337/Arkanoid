#include <vector>
#include <memory>
#include "someFunctions.cpp"
#include "Text.cpp"

int main(int argc, char* argv[])
{
	constexpr size_t windowWidth = 1200;
	constexpr size_t windowHeight = 800;

	std::vector<std::unique_ptr<Rectangle>> rectangles = createRectangles();
	
	float speed = generateSpeed();
	Ball ball(generateCoords(), 400, abs(speed), abs(speed));

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
	
	sf::Texture ballTexture, rectanglesTexture, backgroundTexture;
	if (!ballTexture.loadFromFile("pics/papiez.png")) return -2137;
	if (!rectanglesTexture.loadFromFile("pics/kremowka.png")) return -2137;
	if (!backgroundTexture.loadFromFile("pics/watykan.png")) return -2137;
	

	background.setTexture(&backgroundTexture);
	ball.shape.setTexture(&ballTexture, false);
	for (auto& elem : rectangles)
	{
		elem->shape.setTexture(&rectanglesTexture);
	}

	size_t points = 0;

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
		if (ball.gameOver()) break;
		
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

	return 0;
}