#include <algorithm> //std::transform
#include "MeshManager.h"
#include "OBJ_Loader.h"
//void parseFaceLine(const std::string &line, Face &face);

objl::Loader *loader;

MeshManager::MeshManager()
{
    loader = new objl::Loader();
}
MeshManager::~MeshManager()
{
    delete loader;
}

/// @brief Returns a Mesh object pointer from the mesh map.
/// @param meshName The name of the Mesh as it is stored in the mesh map.
/// @return The Mesh pointer
Mesh *MeshManager::GetMesh(const std::string &meshName)
{
    auto it = meshMap.find(meshName);
    if (it != meshMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}
void MeshManager::Load(const std::string &filename, const std::string &meshName)
{
    Mesh *mesh = new Mesh();
    bool loadout = loader->LoadFile(filename);
    if (loadout)
    {
        std::ofstream file("C:/Users/mstoney/Desktop/dev/cplusplus/e1Out.txt");
        for (int i = 0; i < loader->LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = loader->LoadedMeshes[i];
            file << "Mesh " << i << ": " << curMesh.MeshName << "\n";
            file << "Vertices:\n";

            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                file << "V" << j << ": " << "P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " << "N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " << "TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
            }
            // Print Indices
            file << "Indices:\n";

            // Go through every 3rd index and print the
            //	triangle that these indices represent
            for (int j = 0; j < curMesh.Indices.size(); j += 3)
            {
                file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
            }

            // Print Material
            file << "Material: " << curMesh.MeshMaterial.name << "\n";
            file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
            file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
            file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
            file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
            file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
            file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
            file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
            file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
            file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
            file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
            file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
            file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

            // Leave a space to separate from the next mesh
            file << "\n";
            mesh->vertices.resize(curMesh.Vertices.size());
            std::transform(curMesh.Vertices.begin(), curMesh.Vertices.end(), mesh->vertices.begin(), 
                [](const objl::Vertex& objVert)-> Vertex {
                    return {objVert.Position.X, objVert.Position.Y, objVert.Position.Z};
                }
            );
            mesh->normals.resize(curMesh.Vertices.size());
            std::transform(curMesh.Vertices.begin(), curMesh.Vertices.end(), mesh->normals.begin(), 
                [](const objl::Vertex& objVert)-> Normal {
                    return {objVert.Normal.X, objVert.Normal.Y, objVert.Normal.Z};
                }
            );
            mesh->indices = curMesh.Indices;

        }
        meshMap.insert(std::make_pair(meshName, mesh));
        // Close File
        file.close();
    }
    // If not output an error
    else
    {
        // Create/Open e1Out.txt
        std::ofstream file("e1Out.txt");

        // Output Error
        file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

        // Close File
        file.close();
    }
}
// /// @brief Loads an OBJ file into a Mesh object.
// /// @param filename The location of the OBJ file to load.
// /// @return The Mesh object representing the loaded OBJ file.
// void MeshManager::load(const std::string &filename, const std::string &meshName)
// {
//     Mesh *p_mesh = new Mesh();
//     std::ifstream file(filename);
//     if (!file.is_open())
//     {
//         std::cerr << "Could not open the file: " << filename << std::endl;
//         return;
//     }

//     std::string line;
//     while (std::getline(file, line))
//     {
//         parseLine(line, p_mesh);
//     }
//     for (Face face : p_mesh->faces)
//     {
//         p_mesh->indices.insert(p_mesh->indices.end(), face.vertexIndices.begin(), face.vertexIndices.end());
//     }
//     file.close();
//     meshMap.insert(std::make_pair(meshName, p_mesh));
// }

// /// @brief Tokenizes and parses a single line read in from an OBJ file.
// /// @param line The line to be tokenized and parsed.
// /// @param p_mesh The Mesh object that the OBJ file is being stored as.
// void MeshManager::parseLine(const std::string &line, Mesh *p_mesh)
// {
//     std::istringstream iss(line);
//     std::string prefix;
//     iss >> prefix;

//     if (prefix == "v")
//     {
//         Vertex vertex;
//         iss >> vertex.x >> vertex.y >> vertex.z;
//         p_mesh->vertices.push_back(vertex);
//     }
//     else if (prefix == "vn")
//     {
//         Normal normal;
//         iss >> normal.x >> normal.y >> normal.z;
//         p_mesh->normals.push_back(normal);
//     }
//     else if (prefix == "f")
//     {
//         Face face;
//         std::string faceLine;
//         while (iss >> faceLine)
//         {
//             // OBJ indices are 1-based, convert to 0-based
//             parseFaceLine(faceLine, face);
//         }
//         p_mesh->faces.push_back(face);
//         for (size_t i = 0; i < face.vertexIndices.size(); ++i)
//         {
//             std::cout << "Vertex Index: " << face.vertexIndices[i]
//                       << ", Normal Index: " << face.normalIndices[i] << std::endl;
//         }
//     }
// }

// void parseFaceLine(const std::string &line, Face &face)
// {
//     std::istringstream iss(line);
//     std::string vertexData;

//     while (iss >> vertexData)
//     {
//         std::string vertexIndexStr, normalIndexStr;
//         std::istringstream vertexStream(vertexData);

//         // Extract the vertex index before the first "/"
//         std::getline(vertexStream, vertexIndexStr, '/');

//         // Skip the texture coordinate (empty field between "//")
//         vertexStream.ignore(std::numeric_limits<std::streamsize>::max(), '/');

//         // Extract the normal index after the second "/"
//         std::getline(vertexStream, normalIndexStr, '/');

//         // Convert to integers, subtracting 1 to convert from 1-based OBJ indexing
//         if (!vertexIndexStr.empty())
//         {
//             face.vertexIndices.push_back(std::stoi(vertexIndexStr) - 1);
//         }
//         if (!normalIndexStr.empty())
//         {
//             face.normalIndices.push_back(std::stoi(normalIndexStr) - 1);
//         }
//     }
// }