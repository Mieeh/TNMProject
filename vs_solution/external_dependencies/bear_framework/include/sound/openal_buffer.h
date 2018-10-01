#pragma once

#include<string>

namespace bear { namespace sound { 

	class SoundBuffer {
	private:
		unsigned int m_BufferID;

	public:
		// Default constructor 
		SoundBuffer();

		// Deconstructor 
		~SoundBuffer();

		unsigned int getID() { return m_BufferID; }

		void setBufferSource(std::string a_FilePath);
	};

} } 