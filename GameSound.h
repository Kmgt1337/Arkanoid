#ifndef GAMESOUND_H
#define GAMESOUND_H
#include "SFML\Audio.hpp"

class GameSound
{
public:
	void addSound(std::string path);
	void playSound();

private:
	std::vector<sf::SoundBuffer> buffers;
	std::vector<sf::Sound> sounds;
	static size_t counter;

	void init();
};

#endif

