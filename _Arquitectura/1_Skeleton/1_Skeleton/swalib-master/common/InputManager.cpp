#include "InputManager.h"
#include "sys.h"

#define VK_A 0x41
#define VK_D 0x44
#define VK_SPACE 0x20

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
	else if (SYS_KeyPressed(VK_SPACE)) //Right
	{
		size_t numCallbacks = m_tEventsSpacePressed.size();
		for (size_t i = 0; i < numCallbacks; ++i)
		{
			m_tEventsSpacePressed[i]();
		}
	}
}

void InputManager::Exit()
{

}
