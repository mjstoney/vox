#pragma once
#include <GLFW/glfw3.h>
#include <iostream> // debug remove later
#include "Camera.h"

class InputManager
{
public:
    float cameraSpeed;
    bool W_PRESSED, S_PRESSED, A_PRESSED, D_PRESSED, SPACE_PRESSED, Z_PRESSED;
    bool CURSOR_ENABLED, FIRST_MOUSE;
    int lastX, lastY;

    GLFWwindow* window;
    Camera *camera;
    InputManager(GLFWwindow *window, Camera *cam);
    ~InputManager();

    void ProcessKeyboardInput(int key, int scancode, int action, int mods);
    void ProcessMouseMoveInput(float xpos, float ypos);
    void Update(double deltaTime);
};