#pragma once

#include <glad/glad.h>

struct Face;

class ElementBuffer
{
public:
    unsigned int ID;
    ElementBuffer();
    ElementBuffer(unsigned int* indices, unsigned int size);
    ElementBuffer(Face *indices, unsigned int size)
;    
    ~ElementBuffer();

    void Bind();
    void Unbind();
};