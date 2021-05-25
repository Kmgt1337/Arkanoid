#include "GameSound.h"
#include <random>
#include <iostream>

size_t GameSound::counter = 0;

void GameSound::playSound()
{
	std::random_device seed;
	std::mt19937_64 gen(seed());
	std::uniform_int_distribution<size_t> draw{ 0, sounds.size() - 1};

	sounds.at(draw(gen)).play();
}

void GameSound::addSound(std::string path)
{
	sf::Sound sound;
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile(path))
	{
		exit(-2);
	}

	buffers.push_back(buffer);
	sounds.push_back(sound);

	init();
}

void GameSound::init()
{
	for (size_t i = 0; i < buffers.size(); i++)
	{
		sounds.at(i).setBuffer(buffers.at(i));
	}
}