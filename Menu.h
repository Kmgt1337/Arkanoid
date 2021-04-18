#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Menu
{
public:
	Menu(float width, float heigh);
	~Menu() = default;

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> text;
};

