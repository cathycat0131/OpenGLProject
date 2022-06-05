//
//  Material.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-05.
//

#pragma once

#include <GL/glew.h>

class Material {
public:
    Material();
    Material(GLfloat sIntensity, GLfloat shine);
    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
    ~Material();
private:
    GLfloat specularIntensity;
    GLfloat shininess; //How smooth the surface
};
