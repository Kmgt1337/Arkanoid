#include "SFML\Graphics.hpp"
#include <iostream>

inline sf::Texture makeBallTexture()
{
	sf::Texture ballTexture;
	if (!ballTexture.loadFromFile("pics/papiez.png")) std::cout << "Error" << std::endl;

	return ballTexture;
}

inline sf::Texture makeRectanglesTexture()
{
	sf::Texture rectanglesTexture;
	if (!rectanglesTexture.loadFromFile("pics/kremowka.png")) std::cout << "Error" << std::endl;

	return rectanglesTexture;
}

inline sf::Texture makeBackgroundTexture()
{
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("pics/watykan.png")) std::cout << "Error" << std::endl;

	return backgroundTexture;
}