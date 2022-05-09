#define _USE_MATH_DEFINES

#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "AudioSource.h"
#include "AudioBuffer.h"
#include "Listener.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <string>


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <glfw3.h>
#include <sstream>
#include <vector>

#include <fstream>     
#include <iterator>
#include "litegfx.h"

using namespace std;


int main()
{
	double lastTime = 0;
	double updateTime = glfwGetTime();
	double deltaTime = 0;
	double g = 0;
	char p[] = "prac2 sonido";
	glfwInit();
	GLFWwindow* a = glfwCreateWindow(400, 400, &p[0], NULL, NULL);
	glfwMakeContextCurrent(a);
	lgfx_setup2d(400, 400);


	ALCdevice* device = alcOpenDevice(NULL);
	ALCcontext* Context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(Context);

	//engine.wav no funciona???
	AudioBuffer* buffer = AudioBuffer::load("data/music.wav");

	AudioSource* source = new AudioSource(buffer);

	Listener* listener = new Listener();
	source->play();

	while (!glfwWindowShouldClose(a))
	{
		//Time
		lastTime = updateTime;
		updateTime = glfwGetTime();
		deltaTime = updateTime - lastTime;

		lgfx_clearcolorbuffer(0.5f, 0.5f, 0.5f);
		lgfx_setcolor(1, 0, 0, 1);
		g += (64 * M_PI / 180) * deltaTime;
		source->setPosition(200 + cos(g) * 100 - 10, 200 + sin(g) * 100 - 10, 0);
		lgfx_drawoval(200 + cos(g) * 100 - 10, 200 + sin(g) * 100 - 10, 20, 20);



		if (glfwGetKey(a, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(a, GLFW_KEY_D) == GLFW_PRESS)
		{
			listener->setListenerPosition(listener->posX += 100 * deltaTime, 380, 0);
		}

		if (glfwGetKey(a, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(a, GLFW_KEY_A) == GLFW_PRESS)
		{
			listener->setListenerPosition(listener->posX += -100 * deltaTime, 380, 0);
		}

		lgfx_setcolor(1, 1, 1, 1);
		lgfx_drawoval(listener->posX, 380, 20, 20);

		glfwSwapBuffers(a);
		glfwPollEvents();
	}

	Context = alcGetCurrentContext();
	device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(Context);
	alcCloseDevice(device);

	glfwTerminate();

	return 0;
}
