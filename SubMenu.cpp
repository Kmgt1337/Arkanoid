#include "SubMenu.h"

SubMenu::SubMenu(float width, float height, size_t size, std::vector<std::string> stringVec)
{
	if (!font.loadFromFile("fonts/OpenSans-Regular.ttf"))
	{
		//
	}
	text.resize(size);

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
			text.at(i).setColor(sf::Color::Black);
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
	text.at(selectedItemIndex).setColor(sf::Color::Black);
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
	text.at(selectedItemIndex).setColor(sf::Color::Black);
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
