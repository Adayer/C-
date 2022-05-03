#pragma once

class Listener
{

public:
	float posX = 0;
	float posY = 0;
	float posZ = 0;

	float velX = 0;
	float velY = 0;
	float velZ = 0;

	float oriX = 0;
	float oriY = 0;
	float oriZ = 0;

	Listener();

	void setListenerPosition(float x, float y, float z);
	void setListenerVelocity(float x, float y, float z);
	void setListenerOrientation(float x, float y, float z);

};