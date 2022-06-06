//
//  DirectionalLight.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-06.
//

#pragma once
#include "Light.hpp"
class DirectionalLight: public Light {
public:
    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                     GLfloat aIntensity,GLfloat dIntensity,
                     GLfloat xDir, GLfloat yDir, GLfloat zDir);
    
    //Ambient Lighting
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
                  GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    ~DirectionalLight();
private:
    glm::vec3 direction;

};
