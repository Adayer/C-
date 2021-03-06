#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define STB_IMAGE_IMPLEMENTATION


#include <GL/glew.h>
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "Engine3D.h"
#include "World.h"
#include "Texture.h"
#include "Camera.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	Engine3D* renderEngine = new Engine3D();
	renderEngine->Init();

	World* world = new World();
	world->InitWorld();
	
	// main loop

	//Buffer cosa = Buffer(pruebasVertices, pruebasIndexes);

	float angle = 0;
	float cameraMoveSpeed = 5;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		glm::vec3 cameraOffset(0, 0, 0);
		if (glfwGetKey(win, GLFW_KEY_RIGHT))
		{
			cameraOffset.x += 1;
		}
		else if (glfwGetKey(win, GLFW_KEY_LEFT))
		{
			cameraOffset.x -= 1;
		}
		if (glfwGetKey(win, GLFW_KEY_UP))
		{
			cameraOffset.z -= 1;
		}
		else if (glfwGetKey(win, GLFW_KEY_DOWN))
		{
			cameraOffset.z += 1;
		}
		cameraOffset *= cameraMoveSpeed * deltaTime;
		world->getMainCamera()->Move(cameraOffset);

		world->update(deltaTime);
		world->draw();

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}