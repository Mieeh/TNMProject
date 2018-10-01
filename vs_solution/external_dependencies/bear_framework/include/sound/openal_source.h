#pragma once

#include"openal_buffer.h"

namespace bear { namespace sound { 

	class SoundSource {
	protected:
		SoundBuffer *m_SoundBuffer;
		unsigned int m_SourceID;

	public:
		// Default constructor 
		SoundSource();
		// 
		SoundSource(std::string a_FilePath);

		// Deconstructor
		virtual ~SoundSource();

		// Loads buffer data into source
		void loadSound(std::string a_FilePath);

		// get the source state
		int getState();

		/*
		* Does not care if the source is already playing
		*/
		void play_instantaneous();

		/*
		* Cares if the source if already playing
		*/
		void play();

		/*
		Stops the source use play to start again
		*/
		void stop();

		/*
		Stops the source and resets the track
		*/
		void reset();

		/*
		Stops the source and resets the track & plays it from the start
		*/
		void reset_and_play();

		/*
		Sets the AL_LOOP source information
		*/
		void set_loooping(bool a_Looping);

		/*
		Sets the AL_GAIN source information 
		\param 1 - 0, 1 = max, 0 = silent
		*/
		void setVolume(float a_Volume);

		/*
		Pause and resume track 
		While paused other methods cannot be used on the track
		*/
		void pause();
		void resume();
	};

} } 