#include "CTime.h"
#include <glfw3.h>

void CTime::UpdateDeltaTime()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}
