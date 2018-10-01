#pragma once

/** Sound samples: format specifier. */
#define AL_FORMAT_MONO8                           0x1100
#define AL_FORMAT_MONO16                          0x1101
#define AL_FORMAT_STEREO8                         0x1102
#define AL_FORMAT_STEREO16                        0x1103

#include<fstream>
#include<iostream>

namespace bear { namespace sound { 

	bool WAV_isBigEndian()
	{
		int a = 1;
		return !((char*)&a)[0];
	}

	int WAV_convertToInt(char* buffer, int len)
	{
		int a = 0;
		if (!WAV_isBigEndian())
			for (int i = 0; i<len; i++)
				((char*)&a)[i] = buffer[i];
		else
			for (int i = 0; i<len; i++)
				((char*)&a)[3 - i] = buffer[i];
		return a;
	}

	static char* load_wav(const char* fn, int& chan, int& samplerate, int& bps, int& size, int& format)
	{
		char buffer[4];
		std::ifstream in(fn, std::ios::binary);
		if (!in.is_open()) {
			std::cout << "Failed to open .wav file" << std::endl;
		}

		// Master riff chunk at the first 4 bytes should be "RIFF" if it's a .wav file
		in.read(buffer, 4);
		if (strncmp(buffer, "RIFF", 4) != 0)
		{
			std::cout << "this is not a valid WAVE file" << std::endl;
			return NULL;
		}

		// Still master riff chunk
		in.read(buffer, 4);		// 4+n
		in.read(buffer, 4);     // WAVE

		in.read(buffer, 4);     // fmt
		in.read(buffer, 4);     // Chunk size: 16, 18 or 40
		in.read(buffer, 2);     // Format code: 1
		in.read(buffer, 2);
		chan = WAV_convertToInt(buffer, 2);

		in.read(buffer, 4);		// Sampling rate
		samplerate = WAV_convertToInt(buffer, 4);

		in.read(buffer, 4);		// Data Rate (byte/sec)
		in.read(buffer, 2);		// Data block size (bytes)
		in.read(buffer, 2);		// Bits per sample
		bps = WAV_convertToInt(buffer, 2);

		in.read(buffer, 4);     // Subchunk2ID -> "data"
		in.read(buffer, 4);		// Subchunk2Size -> NumSamples * NumChannels * BitsPerSample/8
		size = WAV_convertToInt(buffer, 4);

		char* data = new char[size];
		in.read(data, size);	// Reading the actual waveform data 

								// Setting the format
		if (chan == 1) {
			if (bps == 8)
				format = AL_FORMAT_MONO8;
			else
				format = AL_FORMAT_MONO16;
		}
		else {
			if (bps == 8)
				format = AL_FORMAT_STEREO8;
			else
				format = AL_FORMAT_STEREO16;
		}

		// Return the waveform data
		return data;
	}

	static int to_al_format(short channels, short samples)
	{
		bool stereo = (channels > 1);

		switch (samples) {
		case 16:
			if (stereo)
				return AL_FORMAT_STEREO16;
			else
				return AL_FORMAT_MONO16;
		case 8:
			if (stereo)
				return AL_FORMAT_STEREO8;
			else
				return AL_FORMAT_MONO8;
		default:
			return -1;
		}
	}

} } 