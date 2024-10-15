#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class InstanceBuffer
{
public:
    unsigned int ID;

    InstanceBuffer(glm::vec3 *transforms, unsigned int size);
    ~InstanceBuffer();
    void Bind();
    void Unbind();
};