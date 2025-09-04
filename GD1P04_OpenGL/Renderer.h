/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : Renderer
 Description : This class contains functionality need to use a camera and shape classes to render a scene and display to the window
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


#pragma once
#include <vector>
#include <memory>
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include "Shape.h"

class cCamera;

class Renderer
{
private:
    std::vector<Shape*> shapes;
    GLuint& Quad_Program;
    float currentTime;

    cCamera& mCamera;

public:
    Renderer(GLuint& Quad_Program, cCamera& _Camera);
    ~Renderer();

    // Shape management
    void addShape(Shape* shape);
    void removeShape(Shape* shape);
    void clearShapes();

    // Rendering
    void updateTime(float time);
    void renderAll();
    void RenderAllAnimated();
};