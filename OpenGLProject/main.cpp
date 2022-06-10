#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GLWindow.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "DirectionalLight.hpp"
#include "CommonValues.h"
#include "SpotLight.hpp"
#include "Model.hpp"

const float toRadians = 3.14159265f / 180.0f;

//Create instances
GLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Material shinyMaterial;
Material dullMaterial;

Texture brickTexture;
Texture buildingTexture;
Texture groundTexture;

Model carModel;

//Calculate time
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

//Animation variables
int pointLightCount = 0;
unsigned int spotLightCount = 0;
bool direction = true;
bool sizeDirection = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement = 0.005f;

float maxSize = 0.8f;
float minSize = 0.4f;
float curAngle = 0.0f;
float curSize = 0.4f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount,
                        GLfloat *vertices, unsigned int verticeCount,
                        unsigned int vLength, unsigned int normalOffset){
    
    for(size_t i = 0; i < indiceCount; i+=3){
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);
        
        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;
        
        vertices[in0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;
        
        vertices[in1] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;
        
        vertices[in2] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
    }
    
    //Going through the vertices row and normalize them
    for(size_t i = 0; i < verticeCount / vLength; i ++){
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        //Paste them back after normalization
        vertices[nOffset] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
    }
}
void CreateObject() {
    
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2 ,3, 0,
        0, 1, 2
    };
    
    GLfloat vertices[] = {
    //    x     y      z          u   v         nx    ny   nz
        -1.0f, -1.0f, -0.0f,     0.0f,0.0f,      0.0f,0.0f,0.0f,
        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,     0.0f,0.0f,0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 0.0f,     0.0f,0.0f,0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 1.0f,     0.0f,0.0f,0.0f
    };
    
    unsigned int floorIndices[] = {
        0, 2, 1,
        1, 2, 3
    };
    
    GLfloat floorVertices[] = {
        -50.0f, 0.0f, -50.0f,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
        50.0f, 0.0f, -50.0f,    50.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        -50.0f, 0.0f, 50.0f,    0.0f, 50.0f,    0.0f, -1.0f, 0.0f,
        50.0f, 0.0f, 50.0f,     50.0f, 50.0f,   0.0f, -1.0f, 0.0f
    };
    
    //Calculate normal vector
    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
    
    //Create new mesh objects
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);
    
    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);
    
    Mesh *obj3 = new Mesh();
    obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
    meshList.push_back(obj3);
}

void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main( void )
{
    mainWindow = GLWindow(1280,1024); //1280, 1024
    mainWindow.Initialize();
     
    CreateObject();
    CreateShaders();
      
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.1f);
    
    brickTexture = Texture("Textures/brick.jpg");
    brickTexture.LoadTexture();
    buildingTexture = Texture("Textures/building.jpg");
    buildingTexture.LoadTexture();
    groundTexture = Texture("Textures/ground.jpeg");
    groundTexture.LoadTexture();
     
    //Create material
    shinyMaterial = Material(4.0f, 256);
    dullMaterial = Material(0.3f, 4);
    
    //Load model
    carModel = Model();
    carModel.LoadModel("Models/cottage.obj");
     
    //Create light instance
    mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
                                 0.1f,0.1f,
                                 0.0f, -1.0f, 0.0f);
     
    pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
                                0.0f, 0.1f,
                                0.0f, 0.0f, 0.0f,
                                0.3f, 0.2f, 0.1f);
    //pointLightCount ++;
    
    pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
                                0.0f, 0.1f,
                                -4.0f, 2.0f, 0.0f,
                                0.3f, 0.2f, 0.1f);
    //pointLightCount ++;
    
    spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
                                0.0f, 0.5f,
                                0.0f, 0.0f,0.0f,
                                0.0f, -1.0f, 0.0f,
                                1.0f, 0.0f, 0.0f,
                                10.0f);
    spotLightCount ++;
     
    spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
                                0.0f, 1.0f,
                                0.0f, -1.5f,0.0f,
                                -100.0f, -1.0f, 0.0f,
                                1.0f, 0.0f, 0.0f,
                                20.0f);
    spotLightCount ++;
    
    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0,
    uniformEyePosition = 0, uniformSpecularIntensity = 0, uniformShininess = 0;
    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)(mainWindow.getBufferWidth() / mainWindow.getBufferHeight()), 0.1f, 100.0f);
    
    /* Loop until the user closes the window */
    while (!mainWindow.getShouldClose()){
        
        //Calculate time
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime; 
        lastTime = now;
        
        // Get + Handle User Input
        glfwPollEvents();
        
        camera.keyControl(mainWindow.getKeys(),deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
         
        //Animation
        if (direction) {
            triOffset += triIncrement;
        } else {
            triOffset -= triIncrement;
        }
        
        if(abs(triOffset) >= triMaxoffset) {
            direction = !direction;
        }
        
        curAngle += 0.5f;
        if(curAngle >= 360) {
            curAngle -= 360;
        }
        
        if(sizeDirection) {
            curSize += 0.01f;
        } else {
            curSize -= 0.01f;
        }
        
        if(curSize >= maxSize || curSize <= minSize) {
            sizeDirection = !sizeDirection;
        }
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Get model uniform setting
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformEyePosition = shaderList[0].GetEyePositionLocation();
        uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
        uniformShininess = shaderList[0].GetShininessLocation();
        
        glm::vec3 lowerLight = camera.getCameraPosition();
        lowerLight.y -= 0.3f;
        spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
        
        shaderList[0].SetDirectionalLight(&mainLight);
        shaderList[0].SetPointLights(pointLights, pointLightCount);
        shaderList[0].SetSpotLights(spotLights, spotLightCount);
        //Put light into action
        //mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);
        
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
        
        //Create model
        glm::mat4 model(1.0f);
        
        //Translate, scale, rotate
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.3f,0.3f, 0.3f));
        
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        
        brickTexture.UseTexture();
        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[0]->RenderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        //model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f,0.3f, 0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        buildingTexture.UseTexture();
        dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[1]->RenderMesh();
        
        //Object 3
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        //model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f,0.3f, 0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        groundTexture.UseTexture();
        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[2]->RenderMesh();
        
        //Object 4
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        //model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f,0.3f, 0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        carModel.RenderModel();
    
        glUseProgram(0);
        
        // Swap front and back buffers
        mainWindow.swapBuffers();
    }
    
    return 0;
}
