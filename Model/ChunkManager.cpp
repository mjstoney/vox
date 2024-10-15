#include "ChunkManager.h"

ChunkManager::ChunkManager(Mesh *mesh)
{
    this->blockMesh = mesh;
    CHUNK_SIZE = 4;
    NUM_CHUNKS_X = 1;
    NUM_CHUNKS_Z = 1;

    Chunk *chunk = nullptr;
    noise = new FastNoiseLite();
    for (int j = 0; j < NUM_CHUNKS_Z; j++)
    {
        for (int i = 0; i < NUM_CHUNKS_X; i++)
        {
            chunk = new Chunk(glm::vec3(i, 0, j), CHUNK_SIZE, noise);
            chunks.push_back(chunk);
        }
    }

    BuildRenderObjects();
}

ChunkManager::~ChunkManager()
{
    for (auto chunk : chunks)
    {
        delete chunk;
    }
    delete noise;
}

void ChunkManager::BuildRenderObjects()
{
    shader = new Shader(
        "C:/Users/mstoney/Desktop/dev/cplusplus/voxels/Shaders/chunk.vert",
        "C:/Users/mstoney/Desktop/dev/cplusplus/voxels/Shaders/chunk.frag");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, blockMesh->vertices.size() * sizeof(Vertex), blockMesh->vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, blockMesh->normals.size() * sizeof(Normal), blockMesh->normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &tbo);
    // glGenBuffers(1, &visibleVBO);
    //  glBindBuffer(GL_ARRAY_BUFFER, tbo);
    //  glBufferData(GL_ARRAY_BUFFER, translations.size() * sizeof(glm::vec3), translations.data(), GL_STATIC_DRAW);
    //  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    //  glEnableVertexAttribArray(2);
    //  glVertexAttribDivisor(2, 1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, blockMesh->indices.size() * sizeof(unsigned int), blockMesh->indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << err;
    }
}

void ChunkManager::InitChunks()
{
}

void ChunkManager::RenderChunks(std::vector<ILightObject *> lights)
{
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBindVertexArray(vao);
    for (auto chunk : chunks)
    {
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, chunk->translations.size() * sizeof(glm::vec3), chunk->translations.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);

        // glBindBuffer(GL_ARRAY_BUFFER, visibleVBO);
        // glBufferData(GL_ARRAY_BUFFER, chunk->blockVisible.size() * sizeof(bool), chunk->blockVisible.data(), GL_STATIC_DRAW);
        // glVertexAttribPointer(3, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(GLubyte), (void *)0);
        // glEnableVertexAttribArray(3);
        // glVertexAttribDivisor(3, 1);

        chunk->Render(shader, lights, blockMesh->indices.size());
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "ChunkManager Render Error: " << err << std::endl;
    }
}

void ChunkManager::UpdateChunks()
{
    for (auto chunk : chunks)
    {
        chunk->Update();
    }
}
