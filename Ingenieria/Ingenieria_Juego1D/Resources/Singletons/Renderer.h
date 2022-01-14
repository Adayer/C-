#pragma once
#include <conio.h>

#define RENDERER_INSTANCE Renderer::GetInstance()

class Renderer
{
private:
	Renderer() {};//Private constructor to ensure it isn't called
	static Renderer* instance;//Static Reference to self

	void MoveCursorToX(int x); //Move typing cursor of console to a set position
	void Clear();//Clears console
public:
	//Singleton functions
	static Renderer* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Renderer();
		}
		return instance;
	}

	//To assure renderer is not copied or created using a copy
	Renderer(Renderer& other) = delete;
	void operator=(const Renderer&) = delete;

	void Init();//Initialize method
	void Update(); //Called to render entities and field
	void Exit(); //Called on app exit
};
