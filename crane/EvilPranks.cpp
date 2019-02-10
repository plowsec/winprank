#include "stdafx.h"
#include "EvilPranks.h"
#include "Constants.h"
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include "resource1.h"
//#include "audioclient.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
/*
TODO ::
- watch
*/
EvilPranks::EvilPranks()
{
	//ctor
}

EvilPranks::~EvilPranks()
{
	//dtor
}

// here, we play the joke
void EvilPranks::beEvil() {
	std::time_t time1 = std::time(NULL);
	std::time_t time2 = std::time(NULL);

	std::cout << "Hello world!" << std::endl;
	waveOutSetVolume(NULL, 0xFFFF);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);

	//play the sound for 10 seconds
	while (abs(time2 - time1) < Constants::PRANK_DURATION) {
		time2 = std::time(NULL);
		//this will flood the output device and override any changment made to its volume. It will also prevent the buddy from muting the speaker.
		setMaxVolume(1.0, true);
	}

	std::cout << "diff : " << time2 - time1 << std::endl;
	PlaySound(NULL, 0, 0);
}

void EvilPranks::setMaxVolume(double nVolume = 1.0, bool bScalar = true)
{

	HRESULT hr = NULL;
	bool decibels = false;
	bool scalar = false;
	double newVolume = nVolume;

	CoInitialize(NULL);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	// -------------------------
	float currentVolume = 0;
	endpointVolume->GetMasterVolumeLevel(&currentVolume);
	//printf("Current volume in dB is: %f\n", currentVolume);

	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	//CString strCur=L"";
	//strCur.Format(L"%f",currentVolume);
	//AfxMessageBox(strCur);

	// printf("Current volume as a scalar is: %f\n", currentVolume);
	if (bScalar == false)
	{
		hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
	}
	else if (bScalar == true)
	{
		hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
	}

	//disable muting :D
	endpointVolume->SetMute(false, NULL);
	endpointVolume->Release();

	CoUninitialize();

}