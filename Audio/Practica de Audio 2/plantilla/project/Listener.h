#pragma once

class Listener
{

public:
	Listener();

	float GetPosX() const { return m_fPosX; }
	float GetPosY() const { return m_fPosY; }
	float GetPosZ() const { return m_fPosZ; }

	float GetVelX() const { return m_fVelX; }
	float GetVelY() const { return m_fVelY; }
	float GetVelZ() const { return m_fVelZ; }
	
	float GetOriX() const { return m_fOriX; }
	float GetOriY() const { return m_fOriY; }
	float GetOriZ() const { return m_fOriZ; }

	void setListenerPosition(float x, float y, float z);
	void setListenerVelocity(float x, float y, float z);
	void setListenerOrientation(float x, float y, float z);

private:
	float m_fPosX = 0;
	float m_fPosY = 0;
	float m_fPosZ = 0;

	float m_fVelX = 0;
	float m_fVelY = 0;
	float m_fVelZ = 0;

	float m_fOriX = 0;
	float m_fOriY = 0;
	float m_fOriZ = 0;

};