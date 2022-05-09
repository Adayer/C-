#pragma once
#include "AudioBuffer.h"

class AudioSource
{
public:

	ALuint sources;
	bool playing = false;

	AudioSource(AudioBuffer* buffer);
	~AudioSource();

	void setPitch(float _pitch)
	{
		alSourcef(sources, AL_PITCH, _pitch);
	};

	void setGain(float _gain)
	{
		alSourcef(sources, AL_GAIN, _gain);
	};

	void setLooping(bool _loop)
	{
		if (_loop)
		{
			alSourcei(sources, AL_LOOPING, 1);
		}
		else
		{
			alSourcei(sources, AL_LOOPING, 0);
		}
	};

	void setPosition(float x, float y, float z)
	{
		alSource3f(sources, AL_POSITION, x, y, z);
	};

	void setVelocity(float x, float y, float z)
	{
		alSource3f(sources, AL_VELOCITY, x, y, z);
	};

	void play();
	void stop();
	void pause();
	bool isPlaying()
	{
		return playing;
	};

};