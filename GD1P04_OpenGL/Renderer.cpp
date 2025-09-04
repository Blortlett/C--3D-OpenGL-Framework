#include "Renderer.h"
#include "Camera/cCamera.h"
#include "cTextureLoader.h"

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

    // Get uniform locations for tiling and flipping 
    GLint textureTilingLoc = glGetUniformLocation(Quad_Program, "TextureTiling");
    GLint flipHorizontalLoc = glGetUniformLocation(Quad_Program, "FlipHorizontal");

    // Render all shapes
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        Shape* shape = shapes[i];
        if (shape)
        {
            // Set tiling and flipping uniforms based on shape
            if (textureTilingLoc != -1)
            {
                if (i == 0) {
                    glUniform2f(textureTilingLoc, 2.0f, 2.0f); // 2x2 tiling for QuadItem
                } else {
                    glUniform2f(textureTilingLoc, 1.0f, 1.0f); // No tiling for cube
                }
            }
            
            if (flipHorizontalLoc != -1)
            {
                glUniform1i(flipHorizontalLoc, (i == 0) ? GL_TRUE : GL_FALSE); // Flip only QuadItem
            }

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

void Renderer::RenderAllAnimated()
{
    glUseProgram(Quad_Program);

    // Send current time to shader
    GLint currentTimeLoc = glGetUniformLocation(Quad_Program, "CurrentTime");
    if (currentTimeLoc != -1)
    {
        glUniform1f(currentTimeLoc, currentTime);
    }

    // Send spritesheet parameters
    GLint sheetSizeLoc = glGetUniformLocation(Quad_Program, "SheetSize");
    if (sheetSizeLoc != -1)
    {
        glUniform2f(sheetSizeLoc, 4.0f, 2.0f); // Spritesheet XY Dimensions
    }

    GLint animSpeedLoc = glGetUniformLocation(Quad_Program, "AnimSpeed");
    if (animSpeedLoc != -1)
    {
        glUniform1f(animSpeedLoc, 12.0f); // FPS
    }

    GLint totalFramesLoc = glGetUniformLocation(Quad_Program, "TotalFrames");
    if (totalFramesLoc != -1)
    {
        glUniform1i(totalFramesLoc, 8); // Total frames in 4x4 grid
    }

    // Set up animated texture uniform
    GLint textureLoc = glGetUniformLocation(Quad_Program, "AnimatedTexture");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 0); // Texture unit 0
    }

    // Render all shapes with animation
    for (auto& shape : shapes)
    {
        if (shape)
        {
            // Update transforms
            shape->updateTransforms();

            // Set up matrices
            glm::mat4 modelMat = shape->getTranslationMatrix() * 
                               shape->getRotationMatrix() * 
                               shape->getScaleMatrix();
            glm::mat4 viewMat = mCamera.GetViewMat();
            glm::mat4 projectionMat = mCamera.GetProjectionMat();

            // Send matrices to shader
            GLint modelMatLoc = glGetUniformLocation(Quad_Program, "ModelMat");
            GLint viewMatLoc = glGetUniformLocation(Quad_Program, "ViewMat");
            GLint projMatLoc = glGetUniformLocation(Quad_Program, "ProjectionMat");

            if (modelMatLoc != -1)
                glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            if (viewMatLoc != -1)
                glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
            if (projMatLoc != -1)
                glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

            // Bind texture for animation
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cTextureLoader::GetInstance().Texture_Orc);

            // Render the shape
            shape->bind();
            if (!shape->getIndices().empty())
            {
                glDrawElements(GL_TRIANGLES, (GLsizei)shape->getIndices().size(), GL_UNSIGNED_INT, 0);
            }
            else if (!shape->getVertices().empty())
            {
                glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(shape->getVertices().size() / 8));
            }
            shape->unbind();
        }
    }

    glUseProgram(0);
}
