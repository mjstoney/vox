#include "ElementBuffer.h"

struct Face;

ElementBuffer::ElementBuffer()
{
    ID = -1;
}
/// @brief Constructor
/// @param indices Array of unsigned int containing indices for drawing
/// @param size The size of the indices array in bytes
ElementBuffer::ElementBuffer(unsigned int* indices, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

ElementBuffer::ElementBuffer(Face *indices, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &ID);
}

/// @brief Bind this element buffer to the context
void ElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

/// @brief Unbind this element buffer from the context
void ElementBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
