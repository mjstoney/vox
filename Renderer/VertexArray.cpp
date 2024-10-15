#include "VertexArray.h"
#include <iostream>
/// @brief Default Constructor generates OpenGL Vertex Array
VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);    
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

/// @brief Binds this Vertex Array to the context
void VertexArray::Bind()
{
    glBindVertexArray(ID);
}

/// @brief Unbinds the Vertex Array from the context
void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

/// @brief Links a Vertex Buffer to this Vertex Array.
/// @param vbo The Vertex Buffer to link.
/// @param layout The location to be used in shaders.
/// @param size The size of the buffer in bytes.
/// @param type The type of elements the Buffer contains.
/// @param stride The size of each vertex in bytes.
/// @param offset The offset number of bytes this layout location begins at within each vertex.
void VertexArray::LinkBuffer(VertexBuffer &vbo, unsigned int layout, unsigned int size, GLenum type, unsigned int stride, void *offset)
{
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

/// @brief Links an Element Buffer to this Vertex Array.
/// @param vbo The Element Buffer to link.
/// @param layout The location to be used in shaders.
/// @param size The size of the buffer in bytes.
/// @param type The type of elements the Buffer contains.
/// @param stride The size of each vertex in bytes.
/// @param offset The offset number of bytes this layout location begins at within each vertex.
void VertexArray::LinkBuffer(ElementBuffer &ebo, unsigned int layout, unsigned int size, GLenum type, unsigned int stride, void *offset)
{
    ebo.Bind();
    this->Bind();
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    ebo.Unbind();
    this->Unbind();
}
void VertexArray::LinkBuffer(InstanceBuffer &ibo, unsigned int layout, unsigned int size, GLenum type, unsigned int stride, void *offset)
{
    ibo.Bind();
    this->Bind();
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    ibo.Unbind();
    this->Unbind();
}
/// @brief Enables the Vertex Attrib Array location for use.
/// @param layout The location to enable.
void VertexArray::Enable(unsigned int layout)
{
    glEnableVertexAttribArray(layout);
}
