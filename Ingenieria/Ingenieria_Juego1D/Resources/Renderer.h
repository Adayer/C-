#pragma once
#include <conio.h>

#define RENDERER_INSTANCE Renderer::GetInstance()

class Renderer
{
private:
	Renderer() {};
	static Renderer* instance;

	void MoveCursorToX(int x);
	void HideCursor(void);
	void Clear();
public:
	static Renderer* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Renderer();
		}
		return instance;
	}

	//To assure Logic Manager is not copied or created using a copy
	Renderer(Renderer& other) = delete;
	void operator=(const Renderer&) = delete;


	void Init();
	void Update();
	void Exit();
};
