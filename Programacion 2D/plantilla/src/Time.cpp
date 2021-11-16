#include "Time.h"
void CTime::UpdateDeltaTime()
{
	double currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}