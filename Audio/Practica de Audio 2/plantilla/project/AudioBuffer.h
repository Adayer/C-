#pragma once
#include "stdint.h"
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "../openal/AL/efx.h"
#include "../openal/AL/efx-creative.h"
#include "../openal/AL/efx-presets.h"

class AudioBuffer
{
private:
	ALuint buffers;

public:
	static AudioBuffer* load(const char* filename);

	ALuint getAlBuffer() const;

	AudioBuffer::AudioBuffer(ALuint aa);
	AudioBuffer::~AudioBuffer();

};