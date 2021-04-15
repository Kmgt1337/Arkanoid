#include <SFML\Graphics.hpp>

inline sf::Text showMessage(size_t points)
{
	sf::Font font;
	font.loadFromFile("fonts/OpenSans-Regular.ttf");

	std::string message = "Points = ";
	message += std::to_string(points);

	sf::Text text(message, font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(10, 10);

	return text;
}