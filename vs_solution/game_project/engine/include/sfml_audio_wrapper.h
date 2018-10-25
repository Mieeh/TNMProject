#pragma once

#include<SFML/Audio.hpp> // Include SFML audio headers

struct Music {
	sf::Music sf_music;

	Music(const std::string& path) {
		printf("Music created wtf\n");
		sf_music.openFromFile(path);
	}

	~Music() {
		//printf("Jak and dexter 3\n");
	}
};

struct SFX {
	sf::SoundBuffer sf_buffer;
	sf::Sound sf_sound;

	SFX(const std::string& path)
	{
		sf_buffer.loadFromFile(path);
		sf_sound.setBuffer(sf_buffer);
		printf("Creating sound\n");
	}

	~SFX()
	{
		printf("Deleting sound\n");
	}
};