//
//  Material.cpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-06-05.
//

#include "Material.hpp"

Material::Material() {
    specularIntensity = 0.0f;
    shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine){
    specularIntensity = sIntensity;
    shininess = shine;
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation){
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}

Material::~Material(){
    
}


