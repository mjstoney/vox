#pragma once

#include <vector>
#include <FastNoiseLite.h>
#include "Chunk.h"

class ChunkManager
{
public:
    std::vector<Chunk*> chunks;
    GLuint vao, vbo, nbo, tbo, visibleVBO, ebo;
    unsigned int CHUNK_SIZE;
    unsigned int NUM_CHUNKS_X, NUM_CHUNKS_Z;

    FastNoiseLite *noise;
    Shader *shader;
    Mesh *blockMesh;
    ChunkManager(Mesh *mesh);
    ~ChunkManager();

    void BuildRenderObjects();
    void InitChunks();
    void RenderChunks(std::vector<ILightObject*> lights);
    void UpdateChunks();
};