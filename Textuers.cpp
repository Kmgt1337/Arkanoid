#include "SFML\Graphics.hpp"
#include <iostream>

inline sf::Texture makeBallTexture()
{
	sf::Texture ballTexture;
	if (!ballTexture.loadFromFile("pics/papiez.png")) std::cout << "Error" << std::endl;

	return ballTexture;
}