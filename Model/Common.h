#pragma once

#include <vector>
#include <iostream>

struct Vertex {
    float x, y, z;
    void print() { std::cout << x << ", " << y << ", " << z << std::endl; }
};

struct Normal {
    float x, y, z;
    void print() { std::cout << x << ", " << y << ", " << z << std::endl; }
};

struct Face {
    std::vector<int> vertexIndices; 
    std::vector<int> normalIndices; 
};