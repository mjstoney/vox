#include "Scene.h"

Scene::Scene(Camera *cam)
{
    gObjManager = new GameObjectManager(cam);
    gObjManager->Init();
}

void Scene::RenderScene() 
{ 
    gObjManager->RenderGameObjects(); 
}

void Scene::UpdateScene(double deltaTime) 
{ 
    gObjManager->UpdateGameObjects(deltaTime); 
}