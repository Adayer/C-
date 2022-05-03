
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "../openal/AL/efx.h"
#include "../openal/AL/efx-creative.h"
#include "../openal/AL/efx-presets.h"
#include "AudioSource.h"

AudioSource::AudioSource(AudioBuffer* buffer)
{
	alGenSources(1, &sources);

	alSourcef(sources, AL_PITCH, pitch);
	alSourcef(sources, AL_GAIN, 1);
	alSourcei(sources, AL_LOOPING, 0);
	alSource3f(sources, AL_POSITION, xPos, 0, 0);
	alSource3f(sources, AL_VELOCITY, 0, 0, 0);

	alSourcei(sources, AL_BUFFER, buffer->getAlBuffer());
}

AudioSource::~AudioSource()
{
}

void AudioSource::play()
{
	alSourcePlay(sources);
	playing = true;
}

void AudioSource::stop()
{
	alSourceStop(sources);
	playing = false;
}

void AudioSource::pause()
{
	alSourcePause(sources);
	playing = false;
}
