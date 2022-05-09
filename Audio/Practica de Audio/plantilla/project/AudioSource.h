#pragma once

#include "AudioBuffer.h"

class AudioSource
{
public:

	ALuint m_uSourcesID;
	bool m_bIsPlaying = false;

	float m_fPitch = 1.0f;
	float m_fXPos = 0.f;

	AudioSource(AudioBuffer* buffer);
	~AudioSource();

	void play();
	void stop();
	void pause();

	bool isPlaying() { return m_bIsPlaying; };

	void setPitch(float _fPitch);
	void offsetPitch(float _fPitchOffset);
	void setPosition(float x, float y, float z);
	void offsetPosition(float x, float y, float z);

	void setGain(float _gain);
	void setLooping(bool _loop);

	void setVelocity(float x, float y, float z);
};