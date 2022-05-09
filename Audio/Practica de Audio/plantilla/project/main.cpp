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
#include "litegfx.h"

int main()
{
	double dBufferTime = 0;
	double dUpdateTime = glfwGetTime();
	double dDeltaTime = 0;
	char sFilename[] = "prac1 sonido";
	glfwInit();
	GLFWwindow* pWindow = glfwCreateWindow(600, 600, &sFilename[0], NULL, NULL);
	glfwMakeContextCurrent(pWindow);

	ALCdevice* pAudioDevice = alcOpenDevice(NULL);
	ALCcontext* pAudioContext = alcCreateContext(pAudioDevice, NULL);
	alcMakeContextCurrent(pAudioContext);

	AudioSource* pSource = new AudioSource(AudioBuffer::load("data/music.wav"));
	Listener* listener = new Listener();
	pSource->play();

	while (!glfwWindowShouldClose(pWindow))
	{
		//Time
		dBufferTime = dUpdateTime;
		dUpdateTime = glfwGetTime();
		dDeltaTime = dUpdateTime - dBufferTime;


		if (glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS|| glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
		{
			pSource->setPitch(-0.1f * dDeltaTime);
		}

		if (glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
		{
			pSource->setPitch(0.1f * dDeltaTime);
		}

		if (glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		{
			pSource->setPosition(1 * dDeltaTime, 0, 0);
		}

		if (glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		{
			pSource->setPosition(-1 * dDeltaTime, 0, 0);
		}

		glfwPollEvents();
	}

	pAudioContext = alcGetCurrentContext();
	pAudioDevice = alcGetContextsDevice(pAudioContext);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(pAudioContext);
	alcCloseDevice(pAudioDevice);

	glfwTerminate();

	return 0;
}
