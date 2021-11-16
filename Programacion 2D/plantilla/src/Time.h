#pragma once
#include <glfw3.h>
class CTime
{
	double previousTime;
	double deltaTime;
public:
	CTime(double _previousTime): deltaTime(0.), previousTime(_previousTime){};
	CTime() {};
	void UpdateDeltaTime();
	double DeltaTime() { return deltaTime; };
};