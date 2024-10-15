#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "InputManager.h"

class Window
{
public:
    unsigned int m_width, m_height;
    GLFWwindow *mp_window;
    static InputManager *inputManager;


    Window(Camera *cam);
    ~Window();
    int Init();
    bool WindowShouldClose();
    void CloseWindow();
    void PollEvents();
    void Render();

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    
    void handle_key_input(int key, int scancode, int action, int mods);
};
