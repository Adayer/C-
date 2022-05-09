#pragma once

#include "../openal/AL/al.h"

class AudioBuffer
{
private:
	ALuint m_uBufferID;

public:
	AudioBuffer::AudioBuffer(ALuint aa) : m_uBufferID(aa){}
	AudioBuffer::~AudioBuffer();

	static AudioBuffer* load(const char* _pFilename);

	ALuint getAlBuffer() const;
};