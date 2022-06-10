//
//  Texture.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-03.
//

#pragma once
#include "stb_image.h"
#include <GL/glew.h>

class Texture {
public:
    Texture();
    Texture(const char* fileLoc);
    
    bool LoadTexture();
    bool LoadTextureA();
    void UseTexture();
    void ClearTexture();
    
    ~Texture();
    
private:
    GLuint textureID;
    int width, height, bitDepth;
    const char* fileLocation;
};
