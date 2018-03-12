// Sound_01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
#include <playsoundapi.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

//typedef signed short BitDepth;//	16bit audio
typedef signed char BitDepth;//	8bit audio
typedef unsigned long long QWORD;

const double pi = 3.141592653589;
const DWORD samplerate = 44100;
const WORD channels = 1;
const unsigned short SOUND_DURATION = 2;//	1 second for example.
const QWORD NUM_SAMPLES = SOUND_DURATION * samplerate * channels;
//const QWORD NUM_SAMPLES = samplerate / 16;

void sineWave(BitDepth buffer[], double freq)
{
	//BitDepth amplitude = 32767 * 0.5;
	BitDepth amplitude = pow(2, 8 * sizeof(BitDepth)) * 0.5;
	QWORD c = 0;
	double d = (samplerate / freq);
	for (QWORD i = 0; i<NUM_SAMPLES; i += channels)
	{
		double deg = 360.0 / d;
		buffer[i] = buffer[i + (1 * (channels - 1))] = sin((c++*deg)*pi / 180)*amplitude;
	}
}

template<typename _Ty> void write(std::ofstream& stream, const _Ty& ty)
{
	stream.write((const char*)&ty, sizeof(_Ty));
}

void writeWaveFile(const char* filename, BitDepth* buffer)
{
	std::ofstream stream(filename, std::ios::binary);

	stream.write("RIFF", 4);
	::write<int>(stream, 36 + (NUM_SAMPLES*sizeof(BitDepth)));
	stream.write("WAVEfmt ", 8);
	::write<int>(stream, 16);
	::write<short>(stream, 1);
	::write<unsigned short>(stream, channels);
	::write<int>(stream, samplerate);
	::write<int>(stream, samplerate*channels*sizeof(BitDepth));
	::write<short>(stream, channels*sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth) * 8);
	stream.write("data", 4);
	::write<int>(stream, NUM_SAMPLES*sizeof(BitDepth));
	stream.write((const char*)&buffer[0], NUM_SAMPLES*sizeof(BitDepth));
	stream.close();
}

/*
int main(int argc, char** argv)
{
	SetConsoleTitleA("PCM Audio Example");

	std::string filename = "Audio";

	BitDepth* buffer = new BitDepth[NUM_SAMPLES];
	memset(buffer, 0, NUM_SAMPLES*sizeof(BitDepth));

	sineWave(buffer, 440.0);


	writeWaveFile(std::string(filename + std::string(".wav")).c_str(), buffer);
	//delete[] buffer;

	PlaySound(TEXT("..\\Sound_01\\Audio.wav"), NULL, SND_FILENAME | SND_SYNC);
	
	sineWave(buffer, 220.0);
	writeWaveFile(std::string(filename + std::string(".wav")).c_str(), buffer);
	delete[] buffer;
	PlaySound(TEXT("..\\Sound_01\\Audio.wav"), NULL, SND_FILENAME | SND_SYNC);

	std::cout << filename << "Done!" << std::endl;
	std::cin.get();

	return 0;
}
*/


int main(int argc, char** argv)
{
	SetConsoleTitleA("PCM Audio Example");

	std::string filename = "Audio";

	BitDepth* buffer = new BitDepth[NUM_SAMPLES];
	memset(buffer, 0, NUM_SAMPLES*sizeof(BitDepth));

	sineWave(buffer, 440.0);


	writeWaveFile(std::string(filename + std::string(".wav")).c_str(), buffer);
	//delete[] buffer;

	PlaySound(TEXT("..\\Sound_01\\Audio.wav"), NULL, SND_FILENAME | SND_SYNC);

	sineWave(buffer, 220.0);
	writeWaveFile(std::string(filename + std::string(".wav")).c_str(), buffer);
	//delete[] buffer;
	PlaySound(TEXT("..\\Sound_01\\Audio.wav"), NULL, SND_FILENAME | SND_SYNC);

	delete[] buffer;
	std::cout << filename << "Done!" << std::endl;
	std::cin.get();

	return 0;
}


