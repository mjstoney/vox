#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "MeshManager.h"
#include "Scene.h"
#include "Camera.h"

class Renderer
{
private:
    Window *window;
    const double FPS = 60.0;
    const double MS_PER_UPDATE = FPS / 1000; 
public:
    Camera *camera;
    Scene *scene;

    Renderer();
    void Load();
    ~Renderer();
    void Run();
    int InitContext();
    void SetClearColor(float r, float g, float b, float a);
    void SetViewport(unsigned int width, unsigned int height);
    void SetDepthTest(bool toggle);
};