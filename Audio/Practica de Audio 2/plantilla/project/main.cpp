#include "../openal/AL/al.h"
#include "../openal/AL/alc.h"
#include "../openal/AL/alext.h"
#include "../openal/AL/alut.h"
#include "AudioSource.h"
#include "AudioBuffer.h"
#include "Listener.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>


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

	double dAngle = 0;
	double dSpeed = 90.f;
	double dRadius = 150.f;
	char sFilename[] = "prac1 sonido";
	glfwInit();
	GLFWwindow* pWindow = glfwCreateWindow(600, 600, &sFilename[0], NULL, NULL);
	glfwMakeContextCurrent(pWindow);
	lgfx_setup2d(600, 600);

	ALCdevice* pAudioDevice = alcOpenDevice(NULL);
	ALCcontext* pAudioContext = alcCreateContext(pAudioDevice, NULL);
	alcMakeContextCurrent(pAudioContext);

	AudioSource* pSource = new AudioSource(AudioBuffer::load("data/music.wav"));
	pSource->setVelocity(10, 10, 10);
	Listener* pListener = new Listener();
	pSource->play();

	while (!glfwWindowShouldClose(pWindow))
	{
		//Time
		dBufferTime = dUpdateTime;
		dUpdateTime = glfwGetTime();
		dDeltaTime = dUpdateTime - dBufferTime;

		lgfx_clearcolorbuffer(0.5f, 0.5f, 0.5f);
		lgfx_setcolor(1, 0, 0, 1);
		dAngle = dAngle + (dSpeed * M_PI / 180.) * dDeltaTime;

		float x = 200. + cos(dAngle) * dRadius;
		float y = 200. + sin(dAngle) * dRadius;
		
		pSource->setPosition(x, y, 0);

		lgfx_drawoval(200. + cos(dAngle) * dRadius, 200. + sin(dAngle) * dRadius, 20.f, 20.f);
		
		if (glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		{
			pListener->setListenerPosition(pListener->GetPosX() + 100 * dDeltaTime, 300, 0);
		}

		if (glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		{
			pListener->setListenerPosition(pListener->GetPosX() - 100. * dDeltaTime, 300.f, 0.f);
		}

		lgfx_setcolor(1, 1, 1, 1);
		lgfx_drawoval(pListener->GetPosX(), 380, 20, 20);
		glfwSwapBuffers(pWindow);
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
