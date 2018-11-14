#pragma once

#include<SFML/Audio.hpp> // Include SFML audio headers

struct Music {
	sf::Music sf_music;

	Music(const std::string& path) {
		sf_music.openFromFile(path);
		//printf("Music created wtf\n");
	}
};

struct SFX {
	sf::SoundBuffer sf_buffer;
	sf::Sound sf_sound;

	SFX(const std::string& path)
	{
		if (!sf_buffer.loadFromFile(path)) {
			printf("Can't do SFX!\n");
		}
		sf_sound.setBuffer(sf_buffer);
		//printf("Creating sound\n");
	}
};