#include "Listener.h"
#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "../openal/AL/efx.h"
#include "../openal/AL/efx-creative.h"
#include "../openal/AL/efx-presets.h"


Listener::Listener()
{
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, 0);
}

void Listener::setListenerPosition(float x, float y, float z)
{
	m_fPosX = x;
	m_fPosY = y;
	m_fPosZ = z;
	alListener3f(AL_POSITION, x, y, z);
}

void Listener::setListenerVelocity(float x, float y, float z)
{
	m_fVelX = x;
	m_fVelY = y;
	m_fVelZ = z;
	alListener3f(AL_VELOCITY, x, y, z);
}

void Listener::setListenerOrientation(float x, float y, float z)
{
	m_fOriX = x;
	m_fOriY = y;
	m_fOriZ = z;
	alListener3f(AL_ORIENTATION, x, y, z);
}