#include "InstanceBuffer.h"

InstanceBuffer::InstanceBuffer(glm::vec3 *transforms, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, transforms, 0);
}

InstanceBuffer::~InstanceBuffer()
{
    glDeleteBuffers(1, &ID);
}

void InstanceBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void InstanceBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
