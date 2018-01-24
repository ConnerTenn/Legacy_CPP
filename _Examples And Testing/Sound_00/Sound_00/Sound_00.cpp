// Sound_00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <playsoundapi.h>
#include <mmsystem.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#pragma comment(lib, "winmm.lib")

using namespace std;

#define PI 3.14159265358979323
#define TAU 2.0 * PI

//Test 0
///*
void PlayAudio()
{
	//cout << PlaySound(TEXT("C:\Sync\Music\Test.mp3"), 0, SND_FILENAME | SND_SYNC | SND_NODEFAULT) << "\n";
	//cout << PlaySoundA("C:\Sync\Music\Test.mp3", 0, SND_FILENAME | SND_SYNC | SND_NODEFAULT) << "\n";
	cout << PlaySound(TEXT("C:\\Sync\\Music\\Test.wave"), NULL, SND_FILENAME | SND_ASYNC) << "\n";
	Sleep(300);
	cout << PlaySound(TEXT("C:\\Sync\\Music\\Test.wav"), NULL, SND_FILENAME | SND_SYNC | SND_NODEFAULT) << "\n";
}
//*/


//Test 1
/*
//-----------------------------------------------------------
// Play an audio stream on the default audio rendering
// device. The PlayAudioStream function allocates a shared
// buffer big enough to hold one second of PCM audio data.
// The function uses this buffer to stream data to the
// rendering device. The inner loop runs every 1/2 second.
//-----------------------------------------------------------


// REFERENCE_TIME time units per second and per millisecond
#define REFTIMES_PER_SEC  10000000
#define REFTIMES_PER_MILLISEC  10000

#define EXIT_ON_ERROR(hres)  \
if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
if ((punk) != NULL)  \
{ (punk)->Release(); (punk) = NULL; }

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

struct MyAudioSource
{
	int FrameSize;
	HRESULT SetFormat(WAVEFORMATEX *pwfx)
	{
		FrameSize = pwfx->nChannels * pwfx->wBitsPerSample;
		return S_OK;
	}
	HRESULT LoadData(UINT32 bufferFrameCount, BYTE *pData, DWORD *flags)
	{
		*pData = sin((bufferFrameCount*TAU) / 50.0) + (FrameSize / 2) * (FrameSize / 2);
		*flags = 0;
		return S_OK;
	}
};

HRESULT PlayAudioStream(MyAudioSource *pMySource)
{
	HRESULT hr;
	REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
	REFERENCE_TIME hnsActualDuration;
	IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDevice *pDevice = NULL;
	IAudioClient *pAudioClient = NULL;
	IAudioRenderClient *pRenderClient = NULL;
	WAVEFORMATEX *pwfx = NULL;
	UINT32 bufferFrameCount;
	UINT32 numFramesAvailable;
	UINT32 numFramesPadding;
	BYTE *pData;
	DWORD flags = 0;

	hr = CoCreateInstance(
	CLSID_MMDeviceEnumerator, NULL,
	CLSCTX_ALL, IID_IMMDeviceEnumerator,
	(void**)&pEnumerator);
	EXIT_ON_ERROR(hr)

	hr = pEnumerator->GetDefaultAudioEndpoint(
	eRender, eConsole, &pDevice);
	EXIT_ON_ERROR(hr)

	hr = pDevice->Activate(
	IID_IAudioClient, CLSCTX_ALL,
	NULL, (void**)&pAudioClient);
	EXIT_ON_ERROR(hr)

	hr = pAudioClient->GetMixFormat(&pwfx);
	EXIT_ON_ERROR(hr)

	hr = pAudioClient->Initialize(
	AUDCLNT_SHAREMODE_SHARED,
	0,
	hnsRequestedDuration,
	0,
	pwfx,
	NULL);
	EXIT_ON_ERROR(hr)

	// Tell the audio source which format to use.
	hr = pMySource->SetFormat(pwfx);
	EXIT_ON_ERROR(hr)

	// Get the actual size of the allocated buffer.
	hr = pAudioClient->GetBufferSize(&bufferFrameCount);
	EXIT_ON_ERROR(hr)

	hr = pAudioClient->GetService(
	IID_IAudioRenderClient,
	(void**)&pRenderClient);
	EXIT_ON_ERROR(hr)

	// Grab the entire buffer for the initial fill operation.
	hr = pRenderClient->GetBuffer(bufferFrameCount, &pData);
	EXIT_ON_ERROR(hr)

	// Load the initial data into the shared buffer.
	hr = pMySource->LoadData(bufferFrameCount, pData, &flags);
	EXIT_ON_ERROR(hr)

	hr = pRenderClient->ReleaseBuffer(bufferFrameCount, flags);
	EXIT_ON_ERROR(hr)

	// Calculate the actual duration of the allocated buffer.
	hnsActualDuration = (double)REFTIMES_PER_SEC *
	bufferFrameCount / pwfx->nSamplesPerSec;

	hr = pAudioClient->Start();  // Start playing.
	EXIT_ON_ERROR(hr)

	// Each loop fills about half of the shared buffer.
	while (flags != AUDCLNT_BUFFERFLAGS_SILENT)
	{
		// Sleep for half the buffer duration.
		Sleep((DWORD)(hnsActualDuration/REFTIMES_PER_MILLISEC/2));

		// See how much buffer space is available.
		hr = pAudioClient->GetCurrentPadding(&numFramesPadding);
		EXIT_ON_ERROR(hr)

		numFramesAvailable = bufferFrameCount - numFramesPadding;

		// Grab all the available space in the shared buffer.
		hr = pRenderClient->GetBuffer(numFramesAvailable, &pData);
		EXIT_ON_ERROR(hr)

		// Get next 1/2-second of data from the audio source.
		hr = pMySource->LoadData(numFramesAvailable, pData, &flags);
		EXIT_ON_ERROR(hr)

		hr = pRenderClient->ReleaseBuffer(numFramesAvailable, flags);
		EXIT_ON_ERROR(hr)
	}

	// Wait for last data in buffer to play before stopping.
	Sleep((DWORD)(hnsActualDuration/REFTIMES_PER_MILLISEC/2));

	hr = pAudioClient->Stop();  // Stop playing.
	EXIT_ON_ERROR(hr)

	Exit:
	CoTaskMemFree(pwfx);
	SAFE_RELEASE(pEnumerator)
	SAFE_RELEASE(pDevice)
	SAFE_RELEASE(pAudioClient)
	SAFE_RELEASE(pRenderClient)

	return hr;
}
*/


//Test 2
/*
void SFMLAudio()
{
	sf::SoundBuffer buffer;
	std::vector<sf::Int16> samples;
	for (int i = 0; i < 1000000; i++)
	{
		samples.push_back(sin((i*TAU) / 100) * 44100);
	}
	cout << buffer.loadFromSamples(&samples[0], samples.size(), 1, 10000) << "\n";
	//if (!buffer.loadFromFile("C:\\Sync\\Music\\Test.wav")) { return; }
	buffer.saveToFile("C:\\Sync\\Music\\Test2.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	//sf::SoundBuffer buffer;
	//if (!buffer.loadFromFile("C:\\Sync\\Music\\Test.wav")) { return; }
	//sf::Sound sound;
	//sound.setBuffer(buffer);
	//sound.play();
}
*/

void main()
{
	PlayAudio();

	//MyAudioSource source;
	//cout << PlayAudioStream(&source) << "\n";

	//SFMLAudio();


	cout << "\nPress Enter To Continue:";
	string Out;
	getline(cin, Out);
}

