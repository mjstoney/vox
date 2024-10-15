#pragma once
#include "MeshManager.h"
#include "ChunkManager.h"
#include <Camera.h>
#include "GameObject.h"
#include "Chunk.h"
class GameObjectManager
{

    //std::vector<GameObject*> gameObjects;
    std::vector<ILightObject*> lightObjects;
    MeshManager *mManager;
    ChunkManager *chunkManager;
    Chunk *chunk;
    Camera *camera;
public:
    GameObjectManager(Camera *cam);
    ~GameObjectManager();
    void Init();

    void RenderGameObjects();
    void UpdateGameObjects(double deltaTime);
};