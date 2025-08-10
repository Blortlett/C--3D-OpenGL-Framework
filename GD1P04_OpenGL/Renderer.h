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

// Implementation
Renderer::Renderer(GLuint program) : shaderProgram(program), currentTime(0.0f)
{
}

Renderer::~Renderer()
{
    clearShapes();
}

void Renderer::addShape(Shape* shape)
{
    if (shape)
    {
        shapes.push_back(shape);
    }
}

void Renderer::removeShape(Shape* shape)
{
    shapes.erase(std::remove(shapes.begin(), shapes.end(), shape), shapes.end());
}

void Renderer::clearShapes()
{
    shapes.clear();
}

void Renderer::updateTime(float time)
{
    currentTime = time;
}

void Renderer::renderAll()
{
    if (shaderProgram == 0) return;

    glUseProgram(shaderProgram);

    // Send current time to shader
    GLint currentTimeLoc = glGetUniformLocation(shaderProgram, "CurrentTime");
    if (currentTimeLoc != -1)
    {
        glUniform1f(currentTimeLoc, currentTime);
    }

    // Render all shapes
    for (auto& shape : shapes)
    {
        if (shape)
        {
            // Update transforms
            shape->updateTransforms();

            // Send transform matrices to shader
            GLint translationLoc = glGetUniformLocation(shaderProgram, "TranslationMat");
            if (translationLoc != -1)
            {
                glUniformMatrix4fv(translationLoc, 1, GL_FALSE,
                    glm::value_ptr(shape->getTranslationMatrix()));
            }

            GLint rotationLoc = glGetUniformLocation(shaderProgram, "RotationMat");
            if (rotationLoc != -1)
            {
                glUniformMatrix4fv(rotationLoc, 1, GL_FALSE,
                    glm::value_ptr(shape->getRotationMatrix()));
            }

            GLint scaleLoc = glGetUniformLocation(shaderProgram, "ScaleMat");
            if (scaleLoc != -1)
            {
                glUniformMatrix4fv(scaleLoc, 1, GL_FALSE,
                    glm::value_ptr(shape->getScaleMatrix()));
            }

            // Render the shape
            shape->render();
        }
    }

    glUseProgram(0);
}