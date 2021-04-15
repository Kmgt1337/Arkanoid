#include <vector>
#include <memory>
#include "someFunctions.cpp"
#include "Text.cpp"

int main(int argc, char* argv[])
{
	constexpr size_t windowWidth = 1200;
	constexpr size_t windowHeight = 800;

	std::vector<std::unique_ptr<Rectangle>> rectangles = createRectangles();
	
	Ball ball(generateCoords(), 200);
	Rectangle rectangle;
	rectangle.setPosition(1000, 700);

	sf::RenderWindow window{ sf::VideoMode(windowWidth, windowHeight), argv[0] };
	window.setFramerateLimit(60);
	window.clear(sf::Color::White);
	sf::Event event;

	sf::Font font;
	font.loadFromFile("fonts/OpenSans-Regular.ttf");

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
		
		for (auto &elem : rectangles)
		{
			window.draw(*elem);
		}
		
		ball.checkRectangle(rectangle.shape.getPosition().x, rectangle.shape.getPosition().y);
		ball.update();
		if (ball.gameOver()) break;
		
		std::string message = "Points = ";
		message += std::to_string(points);

		sf::Text text(message, font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Black);
		text.setPosition(10, 10);

		window.draw(text);
		window.draw(rectangle);
		window.draw(ball);
		window.display();
	}

	return 0;
}