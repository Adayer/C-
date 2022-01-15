#pragma once

#include <functional>
#include <vector>

//#define INPUT_MANAGER_INSTANCE InputManager::GetInstance()

class InputManager
{
private:
	InputManager() {};
	static InputManager*instance;

public:
	static InputManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new InputManager();
		}
		return instance;
	}
	
	//To assure Logic Manager is not copied or created using a copy
	InputManager(InputManager& other) = delete;
	void operator=(const InputManager&) = delete;

	void Init();
	void Update();
	void Exit();


	//Callbacks
	//Left
	using OnLeftPressed = std::function<void()>;
	std::vector<OnLeftPressed> m_tEventsLeftPressed;
	void RegisterOnLeftPressed(OnLeftPressed _cb)
	{
		m_tEventsLeftPressed.push_back(_cb);
	}

	//Right
	using OnRightPressed = std::function<void()>;
	std::vector<OnRightPressed> m_tEventsRightPressed;
	void RegisterOnRightPressed(OnRightPressed _cb)
	{
		m_tEventsRightPressed.push_back(_cb);
	}
	
	//Space
	using OnSpacePressed = std::function<void()>;
	std::vector<OnSpacePressed> m_tEventsSpacePressed;
	void RegisterOnSpacePressed(OnSpacePressed _cb)
	{
		m_tEventsSpacePressed.push_back(_cb);
	}
};