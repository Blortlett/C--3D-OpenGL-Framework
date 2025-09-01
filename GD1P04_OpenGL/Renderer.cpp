#include "Renderer.h"
#include "Camera/cCamera.h"

#include <iostream>
#include <ostream>

Renderer::Renderer(GLuint& _Quad_Program, cCamera& _Camera) : Quad_Program(_Quad_Program), currentTime(0.0f), mCamera(_Camera)
{};

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
    glUseProgram(Quad_Program);

    // Send current time to shader
    GLint currentTimeLoc = glGetUniformLocation(Quad_Program, "CurrentTime");
    if (currentTimeLoc != -1)
    {
        glUniform1f(currentTimeLoc, currentTime);
    }

    // Send blend color to shader
    GLint blendColorLoc = glGetUniformLocation(Quad_Program, "BlendColor");
    if (blendColorLoc != -1)
    {
        glUniform3f(blendColorLoc, 0.0f, 1.0f, 1.0f); // Send this colour (Cyan)
    }

    // Set up texture uniform
    GLint textureLoc = glGetUniformLocation(Quad_Program, "Texture0");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 0); // Texture unit 0
    }
    else {
        std::cout << "No texture0 uniform location!" << std::endl;
    }
    textureLoc = glGetUniformLocation(Quad_Program, "Texture1");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 1); // Texture unit 1
    }

    // Render all shapes
    for (auto& shape : shapes)
    {
        if (shape)
        {
            // Update transforms
            shape->updateTransforms();

            // -= Quad =-
            // Model Matrix
            glm::mat4 modelMat = shape->getTranslationMatrix() * 
                               shape->getRotationMatrix() * 
                               shape->getScaleMatrix();
            // -= Camera =-
            // View Matrix
            glm::mat4 viewMat = mCamera.GetViewMat();
            // Camera's Projection Matrix
            glm::mat4 projectionMat = mCamera.GetProjectionMat();

            // Send combined model matrix to shader
            GLint QuadModelMatLoc = glGetUniformLocation(Quad_Program, "ModelMat");
            GLint viewMatLoc = glGetUniformLocation(Quad_Program, "ViewMat");
            GLint projMatLoc = glGetUniformLocation(Quad_Program, "ProjectionMat");

            if (QuadModelMatLoc == -1)
            {
                std::cout << "Quad Matrix is invalid! @ Renderer::renderAll()" << std::endl;
                //return;
            }
            if (viewMatLoc == -1)
            {
                std::cout << "View Matrix is invalid! @ Renderer::renderAll()" << std::endl;
                //return;
            }
            if (projMatLoc == -1)
            {
                std::cout << "Projection Matrix is invalid! @ Renderer::renderAll()" << std::endl;
                //return;
            }
            
            glUniformMatrix4fv(QuadModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));



            // Render the shape
            shape->render();
        }
    }

    glUseProgram(0);
}