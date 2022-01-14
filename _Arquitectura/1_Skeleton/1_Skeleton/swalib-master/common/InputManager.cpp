#include "InputManager.h"
#include "sys.h"

#define VK_A 0x41
#define VK_D 0x44

InputManager* InputManager::instance = nullptr;

void InputManager::Init()
{
}

void InputManager::Update()
{
	if (SYS_KeyPressed(VK_A)) //Left
	{
		size_t numCallbacks = m_tEventsLeftPressed.size();
		for (size_t i = 0; i < numCallbacks; ++i)
		{
			m_tEventsLeftPressed[i]();
		}
	}
	else if (SYS_KeyPressed(VK_D)) //Right
	{
		size_t numCallbacks = m_tEventsRightPressed.size();
		for (size_t i = 0; i < numCallbacks; ++i)
		{
			m_tEventsRightPressed[i]();
		}
	}
}

void InputManager::Exit()
{

}
