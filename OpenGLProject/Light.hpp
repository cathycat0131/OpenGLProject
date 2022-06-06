//
//  Light.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-04.
//

#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>

class Light {
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,GLfloat dIntensity);
    ~Light();
    
protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    //How much diffuse intensity
    GLfloat diffuseIntensity;
    
};
