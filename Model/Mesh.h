#pragma once
#include <vector>
#include <iostream>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include <ElementBuffer.h>
#include <Shader.h>
#include "Common.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ILightObject;

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;
    std::vector<Face> faces;
    std::vector<unsigned int> indices;


    Mesh();
    ~Mesh() {}

};