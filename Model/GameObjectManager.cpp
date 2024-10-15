#include "GameObjectManager.h"

class PointLight;

GameObjectManager::GameObjectManager(Camera *cam)
{
    mManager = new MeshManager();
     mManager->Load("C:/Users/mstoney/Desktop/dev/cplusplus/voxels/Model/cube.obj", "block");
    //mManager->Load("C:/Users/mstoney/Desktop/dev/cplusplus/samplemodel/box_stack.obj", "block");
    chunkManager = new ChunkManager(mManager->GetMesh("block"));
}

GameObjectManager::~GameObjectManager()
{

    delete mManager;
}

void GameObjectManager::Init()
{
    // Mesh *newMesh = mManager->GetMesh("block");
    // Block *newBlock = new Block(newMesh);
    //  gameObjects.push_back(newBlock);

    PointLight *pLight = new PointLight();
    lightObjects.push_back(pLight);
}

void GameObjectManager::RenderGameObjects()
{
    //chunk->Render(lightObjects);
    chunkManager->RenderChunks(lightObjects);
    // for (auto lightObj : lightObjects)
    // {
    //     if (lightObj->ShouldRender)
    //     {
    //         lightObj->RenderLight();
    //     }
    // }
}

void GameObjectManager::UpdateGameObjects(double deltaTime)
{
    
    chunkManager->UpdateChunks();
    // for (auto gameObj : gameObjects)
    // {
    //     gameObj->Update(deltaTime);
    // }
    // for (auto lightObj : lightObjects)
    // {
    //     lightObj->Update(deltaTime);
    // }
}
