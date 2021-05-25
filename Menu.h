#ifndef MENU_H
#define MENU_H

#include <SFML\Graphics.hpp>
#include <vector>

class Menu
{
public:
	Menu(float width, float height);
	~Menu() = default;

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	size_t getPressedItem();

private:
	size_t selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> text;
};

#endif 

