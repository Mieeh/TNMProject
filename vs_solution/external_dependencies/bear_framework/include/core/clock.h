#pragma once

#include<ctime>

namespace bear { namespace core {

	// Class taken from SudoGameEngine
	// Measures time in milliseconds
	class Clock {
	private:
		clock_t m_startedAt, m_pausedAt;
		bool m_paused, m_started;

	public:
		Clock();

		// Getters
		bool isStarted();
		bool isStopped();
		bool isPaused();
		bool isActive();
		clock_t getTicks();

		// State modifications
		void pause();
		void resume();
		void stop();
		void start();
		void reset();

	};
} }