
#define LITE_GFX_IMPLEMENTATION
#define PI 3.14

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

    GLFWwindow* mainWindow(glfwCreateWindow(800, 800, "Practica 1", nullptr, nullptr));

    glfwMakeContextCurrent(mainWindow);
    lgfx_setup2d(800, 800);



    CTime time;
    double xPos(0.);
    double yPos(0.);
    vec2 mousePos(0.f,0.f);

    double circleRotationSpeed(32.);
    double currentAngle(0.);
    double currentAngleRad(0.);
    double xPosCircle(0.);
    double yPosCircle(0.);

    double distanceFromMouse(100.);

    double distanceMouseToCenter(0.);
    double currentAngleMouseToCircle(0.);
    double currentAngleMouseToCircleRad(0.);
    vec2 screenCenterLocation(400.f, 400.f);
    vec2 rightMiddle(800.f, 400.f);
    vec2 circlePos(0.f, 0.f);

    while (glfwWindowShouldClose(mainWindow) == 0)
    {
        time.UpdateDeltaTime(); 

        glfwPollEvents();

        //Mouse position
        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(mainWindow, 1);
        }

        glfwGetCursorPos(mainWindow, &xPos, &yPos);

        mousePos.x = xPos; 
        mousePos.y = yPos; 


        //Position of the rotating circle around mouse        
        currentAngle = currentAngle - circleRotationSpeed * time.DeltaTime();
        if (currentAngle > 360.)
        {
            currentAngle = currentAngle - 360.;
        }
        currentAngleRad = (currentAngle * PI) / 180.; //Conversion to radianes

        xPosCircle = xPos + cos(currentAngleRad) * distanceFromMouse;
        yPosCircle = yPos + sin(currentAngleRad) * distanceFromMouse;

        circlePos.x = xPosCircle;
        circlePos.y = yPosCircle;
        
        char buffer1[100] = { "\0" };
        vec2 helper(mousePos.x + 100.f, mousePos.y);
        distanceMouseToCenter = Distance(mousePos, screenCenterLocation);
        currentAngleMouseToCircleRad = Angle(helper - mousePos, circlePos - mousePos);
        currentAngleMouseToCircle = (currentAngleMouseToCircleRad * 180.f)/ PI;

        if (currentAngleMouseToCircle < 0)
        {
            currentAngleMouseToCircle = 360.f + currentAngleMouseToCircle;
        }
        sprintf_s(buffer1, "Dis: %.2f, Ang:%.0f", distanceMouseToCenter, currentAngleMouseToCircle);
        
        glfwSetWindowTitle(mainWindow, buffer1);


        //Renderizar cuadro en el centro de la pantalla
        lgfx_clearcolorbuffer(1.f, 1.f, 0.8f);

        //Cuadrado en el medio de la pantalla
        lgfx_setcolor(1,0,0,1);
        lgfx_drawrect(350,350,50,50);

        //Cuadrado en la posicion del ratón
        lgfx_setcolor(0,1,0,1);
        lgfx_drawrect(xPos - 25,yPos - 25,50,50);
        
        //Circulo rotando alrededor del ratón
        lgfx_setcolor(0,0,1,1);
        lgfx_drawoval(xPosCircle - 25, yPosCircle - 25, 50, 50);
        
        glfwSwapBuffers(mainWindow);
    }
    glfwTerminate();
    return 0;
}