#pragma once
class CTime
{
	double previousTime;
	double deltaTime;
	double currentTime;
public:
	CTime(double _previousTime) : deltaTime(0.), previousTime(_previousTime), currentTime(0.) {};
	CTime() : deltaTime(0.), previousTime(0.), currentTime(0.) {};
	void UpdateDeltaTime();
	double DeltaTime() { return deltaTime; };
};

