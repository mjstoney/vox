#include "Chunk.h"

Chunk::Chunk(glm::vec3 position, unsigned int chunkSize, FastNoiseLite *noise)
{
    this->noise = noise;
    heightMap = new int[chunkSize * chunkSize];
    chunkPosition = position;
    CHUNK_SIZE_X = chunkSize;
    CHUNK_SIZE_Y = 256;
    CHUNK_SIZE_Z = chunkSize;
    blockVisible = std::vector<GLubyte>(CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z, 1);

    InitInstances();

    model = glm::mat4(1.0f);
    view = Window::inputManager->camera->GetViewMatrix();
    projection = glm::perspective(glm::radians(60.0f), 1.50f, 0.1f, 100.0f);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << err;
    }
}

Chunk::~Chunk()
{
}

void Chunk::InitInstances()
{
    for (unsigned int x = 0; x < CHUNK_SIZE_X; x++)
    {

        for (unsigned int z = 0; z < CHUNK_SIZE_Z; z++)
        {

            for (unsigned int y = 0; y < CHUNK_SIZE_Y; y++)
            {
                double x_scaled = x * 0.1;
                double y_scaled = y * 0.1;
                double z_scaled = z * 0.1;
                float horizontal_spacing = 0.6f;
                float vertical_spacing = 0.6f;
                float offset = 256.0f;

                glm::vec3 translation = glm::vec3((float)(x + chunkPosition.x) * horizontal_spacing,
                                                  (float)((y - offset + chunkPosition.y) * vertical_spacing),
                                                  (float)(z + chunkPosition.z) * horizontal_spacing);
                translations.push_back(translation);
            }
        }
    }
    for (int i = 0; i < CHUNK_SIZE_X * CHUNK_SIZE_Z; i++)
    {
        float scaled_x = (float)(i % CHUNK_SIZE_X) * 0.1;
        float scaled_z = (float)(i / CHUNK_SIZE_Z) * 0.1;
        // double noise = PerlinNoise::Noise(scaled_x, scaled_z, 0);

        int noiseValue = (int)(256 * noise->GetNoise((float)scaled_x, (float)scaled_z));
        heightMap[i] = noiseValue;
        std::cout << noiseValue << ", ";
    }

    for (int row = 0; row < CHUNK_SIZE_Z; row++)
    {
        for (int col = 0; col < CHUNK_SIZE_X; col++)
        {
            int height = heightMap[CHUNK_SIZE_Z * row + col];
            for (int h = 0; h < CHUNK_SIZE_Y; h++)
            {
                blockVisible[CHUNK_SIZE_X * CHUNK_SIZE_Z * row + CHUNK_SIZE_X * col + h] = h < height ? 1 : 0;
            }
        }
    }
}

void Chunk::Render(Shader *shader, std::vector<ILightObject *> lights, int numIndices)
{
    shader->Use();
    shader->setPointLight("pLight", lights[0]);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0, CHUNK_SIZE_X*CHUNK_SIZE_Y*CHUNK_SIZE_Z);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "Chunk Render Error: " << err << std::endl;
    }
}

void Chunk::Update()
{
    view = Window::inputManager->camera->GetViewMatrix();
    // std::cout << view[0][0] << ", " << view[1][1] << ", " << view[2][2] << ", " << view[3][3] << "\n";
    // std::cout << Window::inputManager->camera->position.z << "\t//\t" << model[3][3] << "\n";
}