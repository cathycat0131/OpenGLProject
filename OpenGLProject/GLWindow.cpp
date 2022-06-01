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
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
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
    return 0;
}

GLWindow::~GLWindow(){
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
