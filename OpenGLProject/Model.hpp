//
//  Model.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-08.
//

#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Texture.hpp"

class Model {
public:
    Model();
    
    void LoadModel(const std::string& filename);
    void RenderModel();
    void ClearModel();
    
    ~Model();
private:
    std::vector<Mesh*> meshList;
    std::vector<Texture*> textureList;
    std::vector<unsigned int> meshToTex;
    
    void LoadNode(aiNode *node, const aiScene *scene);
    void LoadMesh(aiMesh *mesh, const aiScene *scene);
    void LoadMaterial(const aiScene *scene);
};

