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
    Texture(char* fileLoc);
    
    void LoadTexture();
    void UseTexture();
    void ClearTexture();
    
    ~Texture();
    
private:
    GLuint textureID;
    int width, height, bitDepth;
    char* fileLocation;
};
