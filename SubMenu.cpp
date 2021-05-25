#include "SubMenu.h"

SubMenu::SubMenu(float width, float height, std::vector<std::string> stringVec)
{
	if (!font.loadFromFile("fonts/BahamasBold.ttf"))
	{
		//
	}
	text.resize(stringVec.size());

	for (size_t i = 0; i < text.size(); i++)
	{
		text.at(i).setFont(font);
		text.at(i).setColor(sf::Color::Red);
		text.at(i).setString(stringVec.at(i));
		if (i == 0)
		{
			text.at(i).setCharacterSize(100);
			text.at(i).setColor(sf::Color::Red);
		}
		else
		{
			text.at(i).setCharacterSize(50);
			text.at(i).setColor(sf::Color::White);
		}
		text.at(i).setPosition(sf::Vector2f(width / text.size(), height / (text.size() + 1) * (i + 1)));
	}
}

void SubMenu::draw(sf::RenderWindow& window)
{
	for (auto& elem : text)
	{
		window.draw(elem);
	}
}

void SubMenu::moveUp()
{
	text.at(selectedItemIndex).setCharacterSize(50);
	text.at(selectedItemIndex).setColor(sf::Color::White);
	if (selectedItemIndex == 0)
	{
		selectedItemIndex = text.size();
	}
	selectedItemIndex--;

	text.at(selectedItemIndex).setCharacterSize(100);
	text.at(selectedItemIndex).setColor(sf::Color::Red);
}

void SubMenu::moveDown()
{
	text.at(selectedItemIndex).setCharacterSize(50);
	text.at(selectedItemIndex).setColor(sf::Color::White);
	if (selectedItemIndex == text.size() - 1)
	{
		selectedItemIndex = -1;
	}
	selectedItemIndex++;

	text.at(selectedItemIndex).setCharacterSize(100);
	text.at(selectedItemIndex).setColor(sf::Color::Red);
}

size_t SubMenu::getPressedItem()
{
	return selectedItemIndex;
}
