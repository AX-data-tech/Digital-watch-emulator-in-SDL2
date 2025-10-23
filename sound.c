#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#define SAMPLE_RATE 44100

void beep(double frequency, int duration_ms)
{
	SDL_AudioSpec want, have;
	SDL_AudioDeviceID dev;
	SDL_memset(&want, 0, sizeof(want));

	want.freq = SAMPLE_RATE;
	want.format = AUDIO_F32SYS;
	want.channels = 1;
	want.samples = 4096;

	dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
	if (dev == 0)
	{
		printf("Failed to open audio %s\n", SDL_GetError());
		return;
	}

	int sampleCount = (int)((duration_ms / 1000.0) * have.freq);
	float *buffer = (float*)SDL_malloc(sampleCount * sizeof(float));

	double phase = 0.0;
	double phaseIncrement = 2.0* M_PI * frequency / have.freq;
	for (int i = 0; i < sampleCount; i++)
	{
		buffer[i] = (float)sin(phase);
		phase += phaseIncrement;
	}

	SDL_QueueAudio(dev, buffer, sampleCount * sizeof(float));
	SDL_PauseAudioDevice(dev, 0);

	SDL_Delay(duration_ms + 50);
	SDL_CloseAudioDevice(dev);
	SDL_free(buffer);
}
