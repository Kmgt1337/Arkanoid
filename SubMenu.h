#ifndef SUBMENU_H
#define SUBMENU_H
#include <SFML\Graphics.hpp>
#include <vector>

class SubMenu
{
public:
	SubMenu(float width, float height, std::vector<std::string> stringVec);
	~SubMenu() = default;

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