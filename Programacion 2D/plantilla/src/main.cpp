
#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "vector2.h"
#include "Time.h"

using namespace std;

int main() {
    if (!glfwInit()) {
        return 0;
    }

    GLFWwindow* mainWindow(glfwCreateWindow(1000, 1000, "Practica 1", nullptr, nullptr));
    lgfx_setup2d(1000, 1000);

    glfwMakeContextCurrent(mainWindow);

    CTime time;

    while (glfwWindowShouldClose(mainWindow) != 0)
    {
        time.UpdateDeltaTime(); 
        //Renderizar cuadro en el centro de la pantalla
        




        glfwPollEvents();
        glfwSwapBuffers(mainWindow);
        lgfx_clearcolorbuffer(0.5f, 0, 0);
    }
    glfwTerminate();
    return 0;
}