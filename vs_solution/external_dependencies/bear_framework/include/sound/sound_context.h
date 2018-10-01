#pragma once

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;

namespace bear { namespace sound { 

	class SoundContext {
	private:
		static ALCdevice* m_Device;
		static ALCcontext* m_Context;

	private:
		SoundContext() { } // Private constructor 

	public:
		// Inits OpenAL for use
		static void init();

		// OpenAL deconstruction
		static void exit();
	};

} } 