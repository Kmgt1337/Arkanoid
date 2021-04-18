#include "SFML\Graphics.hpp"
#include <iostream>

inline sf::Texture makeBallTextureRight()
{
	sf::Texture ballTexture;
	if (!ballTexture.loadFromFile("pics/papiezprawy.png")) std::cout << "Error" << std::endl;

	return ballTexture;
}

inline sf::Texture makeBallTextureLeft()
{
	sf::Texture ballTexture;
	if (!ballTexture.loadFromFile("pics/papiezlewy.png")) std::cout << "Error" << std::endl;

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