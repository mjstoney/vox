#pragma once

#include <unordered_map>
#include "Mesh.h"



class MeshManager
{
public:
    std::unordered_map<std::string, Mesh*> meshMap;
 
    MeshManager();
    ~MeshManager();

    Mesh *GetMesh(const std::string &meshName);
    void Load(const std::string &filename, const std::string &meshName);
    //void parseLine(const std::string &line, Mesh *p_mesh);
};