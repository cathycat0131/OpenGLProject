//
//  GLWindow.cpp
//  OpenGLProject
//
//  Created by Cathy Chen on 2022-05-31.
//

#include "GLWindow.hpp"

GLWindow::GLWindow(){
    width = 800;
    height = 600;
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = 0;
    }
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = 0;
    }
}

int GLWindow::Initialize(){
    
    // Initialize the library
    if ( !glfwInit( ) )
    {   printf("GLFW initialisation failed!");
        glfwTerminate();
        return -1;
    }
    
    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forward Compatbility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create a windowed mode window and its OpenGL context
    mainWindow = glfwCreateWindow( width, height, "Hello World", NULL, NULL );
    
    if ( !mainWindow )
    {   printf("GLFW window creation failed!");
        glfwTerminate( );
        return -1;
    }
    
    // Get Buffer Size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);
    
    //Handle Keys + Mouse input
    createCallBacks();

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}
void GLWindow::createCallBacks() {
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void GLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if(key >= 0 && key < 1024) {
        if(action == GLFW_PRESS) {
            theWindow->keys[key] = true;
        }else if(action == GLFW_FALSE) {
            theWindow->keys[key] = false;
        }
    }
}

void GLWindow::handleMouse(GLFWwindow* window, double xPos, double yPos){
    GLWindow* theWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
    
    if(theWindow->mousedFirstMoved) {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mousedFirstMoved = false;
    }
    
    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;
    
    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
    
    printf("X: %6f, y:%.6f\n", theWindow->xChange, theWindow->yChange);
}

GLWindow::~GLWindow(){
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
