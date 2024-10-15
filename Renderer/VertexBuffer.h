#pragma once
#include <glad/glad.h>
#include "Common.h"

class VertexBuffer
{
public:
    unsigned int ID;
    VertexBuffer();
    VertexBuffer(float *vertices, unsigned int size);
    VertexBuffer(Vertex *vertices, unsigned int size);
    VertexBuffer(Normal *normals, unsigned int size);
    ~VertexBuffer();

    void Bind();
    void Unbind();
};