#pragma once
#include <vector>
#include <memory>
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include "Shape.h"

class Renderer
{
private:
    std::vector<Shape*> shapes;
    GLuint shaderProgram;
    float currentTime;

public:
    Renderer(GLuint program);
    ~Renderer();

    // Shape management
    void addShape(Shape* shape);
    void removeShape(Shape* shape);
    void clearShapes();

    // Rendering
    void updateTime(float time);
    void renderAll();

    // Shader management
    void setShaderProgram(GLuint program) { shaderProgram = program; }
    GLuint getShaderProgram() const { return shaderProgram; }

    // Utility
    size_t getShapeCount() const { return shapes.size(); }
};