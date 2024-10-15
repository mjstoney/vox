#pragma once

#include "GameObjectManager.h"
#include "Camera.h"

class Scene
{
public:
    GameObjectManager *gObjManager;


    Scene(Camera *cam) ;
    ~Scene() {}

    void RenderScene();
    void UpdateScene(double deltaTime);
};