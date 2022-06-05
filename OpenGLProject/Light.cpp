//
//  Light.cpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-04.
//

#include "Light.hpp"

Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    diffuseIntensity = 0;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
             GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity){
    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
    direction = glm::vec3(xDir,yDir,zDir);
    diffuseIntensity = dIntensity;
}

//Ambient directional lighting
void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
                     GLfloat diffuseIntensityLocation, GLfloat directionLocation){
    //Attach ambient light
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    
    //Attach diffuse tensity
    glUniform3f(directionLocation, direction.x,direction.y,direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

Light::~Light(){
    
}
