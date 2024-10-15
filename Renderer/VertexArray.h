#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "InstanceBuffer.h"

class VertexArray
{
public:
    unsigned int ID;
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();
    void LinkBuffer(VertexBuffer &vbo, unsigned int layout, unsigned int size, GLenum type, unsigned int stride, void* offset);
    void LinkBuffer(ElementBuffer &ebo, unsigned int layout, unsigned int size, GLenum type, unsigned int stride, void* offset);
    void LinkBuffer(InstanceBuffer &ibo, unsigned int layout, unsigned int size, GLenum type, unsigned int stride, void* offset);
    void Enable(unsigned int layout);
};