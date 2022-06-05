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
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
          GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
    
    //Ambient Lighting
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
                  GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    
    
    ~Light();
    
private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    
    glm::vec3 direction;
    //How much diffuse intensity
    GLfloat diffuseIntensity;
    
};
