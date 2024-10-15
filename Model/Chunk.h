#pragma once
#include "InstanceBuffer.h"
#include "Mesh.h"
#include "Window.h"
#include <FastNoiseLite.h>

class Chunk
{
private:
    unsigned int CHUNK_SIZE_X;
    unsigned int CHUNK_SIZE_Y;
    unsigned int CHUNK_SIZE_Z;
public:
    
    glm::vec3 chunkPosition;
    std::vector<glm::vec3> translations;
    std::vector<GLubyte> blockVisible;
    int *heightMap;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    FastNoiseLite *noise;

    
    Chunk(glm::vec3 position, unsigned int chunkSize, FastNoiseLite *noise);
    ~Chunk();
    void InitInstances();
    void Render(Shader *shader, std::vector<ILightObject*> lights, int numIndices);
    void Update();
};