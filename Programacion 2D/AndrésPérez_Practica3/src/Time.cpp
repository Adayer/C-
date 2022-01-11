#include "Time.h"
#include <stdio.h>

void CTime::UpdateDeltaTime()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}