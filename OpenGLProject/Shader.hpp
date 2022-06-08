//
//  Shader.hpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-05-31.
//

#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "CommonValues.h"
#include "SpotLight.hpp"

class Shader {
public:
    Shader();
    
    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
    
    std::string ReadFile(const char* fileLocation);
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColourLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    GLuint GetEyePositionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    
    void SetDirectionalLight(DirectionalLight * dLight);
    void SetPointLights(PointLight * pLight, unsigned int lightCount);
    void SetSpotLights(SpotLight * sLight, unsigned int lightCount);
    
    void UseShader();
    void ClearShader();
    
    ~Shader();
    
private:
    int pointLightCount;
    int spotLightCount;
    
    GLuint shaderID, uniformProjection, uniformModel, uniformView,uniformEyePosition,
    uniformSpecualrIntensity, uniformShininess;
    
    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        GLuint uniformDirection;
        GLuint uniformPosition;
    } uniformDirectionalLight;
    
    GLuint uniformPointLightCount;
    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        GLuint uniformDirection;
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    } uniformPointLight[MAX_POINT_LIGHTS];
    
    GLuint uniformSpotLightCount;
    
    struct {
        GLuint uniformColour;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;
        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
        
        GLuint uniformDirection;
        GLuint uniformEdge;
    } uniformSpotLight[MAX_SPOT_LIGHTS];
    
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
