#define STB_IMAGE_IMPLEMENTATION

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GLWindow.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Light.hpp"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

const float toRadians = 3.14159265f / 180.0f;

//Create instances
GLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
Light mainLight;

Texture brickTexture;
Texture buildingTexture;

//Calculate time
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

//Animation variables
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

void CreateObject() {
    
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2 ,3, 0,
        0, 1, 2
    };
    
    GLfloat vertices[] = {
    //    x     y      z      u   v
        -1.0f, -1.0f, 0.0f, 0.0f,0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f
    };
    
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj1);
    
    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj2);
}

void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main( void )
{
    mainWindow = GLWindow(800,600);
    mainWindow.Initialize();
    
    CreateObject();
    CreateShaders();
     
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 1.0f, 0.1f);
    
    brickTexture = Texture("Textures/brick.jpg");
    brickTexture.LoadTexture();
    buildingTexture = Texture("Textures/building.jpg");
    buildingTexture.LoadTexture();
    
    //Create light instance
    mainLight = Light(0.0f, 1.0f, 1.0f, 0.5f);
    
    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColour = 0;
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
            curSize += 0.001f;
        } else {
            curSize -= 0.001f;
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
        uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
        uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
        
        //Put light into action
        mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour);
        
        //Create model
        glm::mat4 model(1.0f);
        
        //Translate, scale, rotate
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.5f));
        model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f,0.3f, 0.3f));
        
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        brickTexture.UseTexture();
        meshList[0]->RenderMesh();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.5f));
        model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f,0.3f, 0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        buildingTexture.UseTexture();
        meshList[1]->RenderMesh();
    
        glUseProgram(0);
        
        // Swap front and back buffers
        mainWindow.swapBuffers();
    }
    
    return 0;
}
