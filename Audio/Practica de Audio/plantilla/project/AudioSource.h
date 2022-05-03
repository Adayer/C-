#pragma once
#include "AudioBuffer.h"

class AudioSource
{
public:

	ALuint sources;
	bool playing = false;

	float pitch = 1;
	float xPos = 0;

	AudioSource(AudioBuffer* buffer);
	~AudioSource();

	void setPitch(float _pitch)
	{
		if (pitch > 0.5f && pitch < 2)
		{
			pitch += _pitch;
		}
		else if(pitch<=0.5f)
		{
			pitch = 0.6f;
		}
		else if (pitch >= 2)
		{
			pitch = 1.9f;
		}

		alSourcef(sources, AL_PITCH, pitch);
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
		xPos += x;
		alSource3f(sources, AL_POSITION, xPos, y, z);
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