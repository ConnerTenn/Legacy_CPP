
#include "portaudio.h"
#include <iostream>
#include <string>

#define SAMPLE_RATE (44100)
//#define SAMPLE_RATE (8000)
#define PI 3.14159265358979323
#define TAU (2.0*PI)

typedef int PaStreamCallback(const void *input,
	void *output,
	unsigned long frameCount,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData);

struct paTestData
{
	float Waveform = 0;
	float Offset = 0.02;
	uint32_t i = 0;
	uint8_t n = 0;
	uint8_t s = 0;
} data;


int g(int i, int x, int t, int o)
{
	return ((3 & x & (i * ((3 & i >> 16 ? "BY}6YB6%" : "Qj}6jQ6%")[t % 8] + 51) >> o)) << 4);
}

/* This routine will be called by the PortAudio engine when audio is needed.
It may called at interrupt level on some machines so don't do anything
that could mess up the system like calling malloc() or free().
*/
static int patestCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	/* Cast data passed through stream to our structure. */
	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	unsigned int i;

	for (i = 0; i<framesPerBuffer; i++)
	{
		//*out = sin(data->Waveform);  /* left */
		//out++;
		//*out = 0;// sin(data->Waveform);//((data->Waveform/TAU) * 2.0) - 1.0;  /* right */
		//out++;

		//data->Waveform += data->Offset;
		//data->Waveform = fmodf(data->Waveform, TAU);
		//if (data->Waveform > TAU) { data->Waveform = data->Waveform - TAU; }
		//data->Offset += 0.0001; if (data->Offset > 0.3) { data->Offset = data->Offset - (0.3 - 0.04); }

		uint32_t &i = data->i;
		uint8_t &s = data->s;
		uint8_t &n = data->n;
		int val = g(i, 1, n = i >> 14, 12) +
			g(i, s = i >> 17, n^i >> 13, 10) +
			g(i, s / 3, n + ((i >> 11) % 3), 10) +
			g(i, s / 5, 8 + n - ((i >> 10) % 3), 9);
		i++;
		static int qq = 0; qq++; if (qq >= 5) { qq = 0; }
		*out = ((float)qq) / ((float)(5)) - 1.0;
		out++;
	}
	return 0;
}

void main()
{
	PaStream *stream;
	PaError err;

	err = Pa_Initialize();

	std::cout << "PortAudio:: " << Pa_GetErrorText(err) << "\n";

	/* Open an audio I/O stream. */
	err = Pa_OpenDefaultStream(&stream,
		0,          /* no input channels */
		1,          /* stereo output */
		paFloat32,  /* 32 bit floating point output */
		SAMPLE_RATE,
		256,        /* frames per buffer, i.e. the number
					of sample frames that PortAudio will
					request from the callback. Many apps
					may want to use
					paFramesPerBufferUnspecified, which
					tells PortAudio to pick the best,
					possibly changing, buffer size.*/
		patestCallback, /* this is your callback function */
		&data); /*This is a pointer that will be passed to
				your callback*/
	std::cout << "PortAudio:: " << Pa_GetErrorText(err) << "\n";

	err = Pa_StartStream(stream);
	std::cout << "PortAudio:: " << Pa_GetErrorText(err) << "\n";

	//Pa_Sleep(5000);
	std::string out = "Press Enter To Contiune"; std::cout << out; std::getline(std::cin, out);

	err = Pa_StopStream(stream);
	std::cout << "PortAudio:: " << Pa_GetErrorText(err) << "\n";

	err = Pa_Terminate();
	std::cout << "PortAudio:: " << Pa_GetErrorText(err) << "\n";

}

