#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "AudioSource.h"
#include "AudioBuffer.h"
#include "Listener.h"


#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#define _CRT_SECURE_NO_WARNINGS

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
	char p[] = "prac1 sonido";
	glfwInit();
	GLFWwindow* a = glfwCreateWindow(600, 600, &p[0], NULL, NULL);
	glfwMakeContextCurrent(a);


	ALCdevice* device = alcOpenDevice(NULL);
	ALCcontext* Context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(Context);


	AudioBuffer* buffer = AudioBuffer::load("data/music.wav");

	AudioSource* source = new AudioSource(buffer);

	Listener* listener = new Listener();
	source->play();

	if (source->isPlaying())
	{
		printf("Sonando musicas\n");
	}

	while (!glfwWindowShouldClose(a))
	{
		//Time
		lastTime = updateTime;
		updateTime = glfwGetTime();
		deltaTime = updateTime - lastTime;


		if (glfwGetKey(a, GLFW_KEY_DOWN) == GLFW_PRESS|| glfwGetKey(a, GLFW_KEY_S) == GLFW_PRESS)
		{
			source->setPitch(-0.1f * deltaTime);
		}

		if (glfwGetKey(a, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(a, GLFW_KEY_W) == GLFW_PRESS)
		{
			source->setPitch(0.1f * deltaTime);
		}

		if (glfwGetKey(a, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(a, GLFW_KEY_D) == GLFW_PRESS)
		{
			source->setPosition(1 * deltaTime, 0, 0);
		}

		if (glfwGetKey(a, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(a, GLFW_KEY_A) == GLFW_PRESS)
		{
			source->setPosition(-1 * deltaTime, 0, 0);
		}

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
