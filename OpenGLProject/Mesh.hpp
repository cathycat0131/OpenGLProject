//
//  Mesh.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-05-31.
//

#pragma once

#include <GL/glew.h>

class Mesh {
public:
    Mesh();
    
    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();
    
    ~Mesh();
    
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};

