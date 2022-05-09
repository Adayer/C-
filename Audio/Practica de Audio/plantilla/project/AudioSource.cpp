#include "AudioSource.h"

#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "../openal/AL/efx.h"
#include "../openal/AL/efx-creative.h"
#include "../openal/AL/efx-presets.h"

AudioSource::AudioSource(AudioBuffer* buffer)
{
	alGenSources(1, &m_uSourcesID);

	alSourcef(m_uSourcesID, AL_PITCH, m_fPitch);
	alSourcef(m_uSourcesID, AL_GAIN, 1);
	alSourcei(m_uSourcesID, AL_LOOPING, 0);
	alSource3f(m_uSourcesID, AL_POSITION, m_fXPos, 0, 0);
	alSource3f(m_uSourcesID, AL_VELOCITY, 0, 0, 0);

	alSourcei(m_uSourcesID, AL_BUFFER, buffer->getAlBuffer());
}

AudioSource::~AudioSource()
{
}
void AudioSource::play()
{
	alSourcePlay(m_uSourcesID);
	m_bIsPlaying = true;
}
void AudioSource::stop()
{
	alSourceStop(m_uSourcesID);
	m_bIsPlaying = false;
}
void AudioSource::pause()
{
	alSourcePause(m_uSourcesID);
	m_bIsPlaying = false;
}

void AudioSource::setPitch(float _pitch)
{
	m_fPitch = _pitch;
	if (m_fPitch < 0.5f )
	{
		m_fPitch = 0.5f;
	}
	else if (m_fPitch >= 2)
	{
		m_fPitch = 2.f;
	}
	
	alSourcef(m_uSourcesID, AL_PITCH, m_fPitch);

}
void AudioSource::offsetPitch(float _fPitchOffset)
{
	m_fPitch += _fPitchOffset;

	if (m_fPitch < 0.5f)
	{
		m_fPitch = 0.5f;
	}
	else if (m_fPitch > 2)
	{
		m_fPitch = 2.f;
	}
	alSourcef(m_uSourcesID, AL_PITCH, m_fPitch);
};
void AudioSource::setGain(float _gain)
{
	alSourcef(m_uSourcesID, AL_GAIN, _gain);
};
void AudioSource::setLooping(bool _loop)
{
	if (_loop)
	{
		alSourcei(m_uSourcesID, AL_LOOPING, 1);
	}
	else
	{
		alSourcei(m_uSourcesID, AL_LOOPING, 0);
	}
};
void AudioSource::setPosition(float x, float y, float z)
{
	m_fXPos = x;
	alSource3f(m_uSourcesID, AL_POSITION, m_fXPos, y, z);
};
void AudioSource::offsetPosition(float x, float y, float z)
{
	m_fXPos += x;
	alSource3f(m_uSourcesID, AL_POSITION, m_fXPos, y, z);
};
void AudioSource::setVelocity(float x, float y, float z)
{
	alSource3f(m_uSourcesID, AL_VELOCITY, x, y, z);
};