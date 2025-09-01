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
    GLuint CameraShaderProgram;
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