#include "Menu.h"

Menu::Menu(float width, float heigh)
{
	if (!font.loadFromFile("fonts/OpenSans-Regular.ttf"))
	{
		//
	}
	text.resize(3);
	text.at(0).setFont(font);
	text.at(0).setColor(sf::Color::Red);
	text.at(0).setString("ZAGRAJ");
	text.at(0).setCharacterSize(100);
	text.at(0).setPosition(sf::Vector2f(width / 3, heigh / (text.size() + 1) * 1));

	text.at(1).setFont(font);
	text.at(1).setColor(sf::Color::Black);
	text.at(1).setString("OPCJE");
	text.at(1).setCharacterSize(50);
	text.at(1).setPosition(sf::Vector2f(width / 3, heigh / (text.size() + 1) * 2));

	text.at(2).setFont(font);
	text.at(2).setColor(sf::Color::Black);
	text.at(2).setString("WYJDZ");
	text.at(2).setCharacterSize(50);
	text.at(2).setPosition(sf::Vector2f(width / 3, heigh / (text.size() + 1) * 3));

	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
	for (auto& elem : text)
	{
		window.draw(elem);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text.at(selectedItemIndex).setCharacterSize(50);
		text.at(selectedItemIndex).setColor(sf::Color::Black);
		
		selectedItemIndex--;
		
		text.at(selectedItemIndex).setCharacterSize(100);
		text.at(selectedItemIndex).setColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 <= text.size())
	{
		text.at(selectedItemIndex).setCharacterSize(50);
		text.at(selectedItemIndex).setColor(sf::Color::Black);
		
		selectedItemIndex++;
		
		text.at(selectedItemIndex).setCharacterSize(100);
		text.at(selectedItemIndex).setColor(sf::Color::Red);
	}
}

