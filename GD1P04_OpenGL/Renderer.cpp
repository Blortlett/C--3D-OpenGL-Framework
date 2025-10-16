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


#include "Renderer.h"
#include "cCamera.h"
#include "cTextureLoader.h"
#include "cSkybox.h"

#include <iostream>
#include <ostream>

Renderer::Renderer(GLuint& _Program, GLuint& _Skybox_Program, cCamera& _Camera) 
    : Render_Program(_Program)
    , Skybox_Program(_Skybox_Program)
    , currentTime(0.0f)
    , mCamera(_Camera)
{};

Renderer::~Renderer()
{
    clearShapes();
}

void Renderer::addMeshModel(cMeshModel* model)
{
    if (model)
    {
        meshModels.push_back(model);
    }
}

void Renderer::removeMeshModel(cMeshModel* model)
{
    meshModels.erase(std::remove(meshModels.begin(), meshModels.end(), model),
        meshModels.end());
}

void Renderer::clearMeshModels()
{
    meshModels.clear();
}

void Renderer::RenderAllMeshModels()
{
    glUseProgram(Render_Program);

    // Send current time to shader
    GLint currentTimeLoc = glGetUniformLocation(Render_Program, "CurrentTime");
    if (currentTimeLoc != -1)
    {
        glUniform1f(currentTimeLoc, currentTime);
    }

    // Set up texture uniform (assuming single texture for now)
    GLint textureLoc = glGetUniformLocation(Render_Program, "Texture0");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 0); // Texture unit 0
    }

    // Render all mesh models
    for (auto& model : meshModels)
    {
        if (model)
        {
            // Update transforms
            model->UpdateTransforms();

            // Create model matrix
            glm::mat4 modelMat = model->GetTranslationMatrix() *
                model->GetRotationMatrix() *
                model->GetScaleMatrix();

            // Get camera matrices
            glm::mat4 viewMat = mCamera.GetViewMat();
            glm::mat4 projectionMat = mCamera.GetProjectionMat();

            // Send matrices to shader
            GLint modelMatLoc = glGetUniformLocation(Render_Program, "ModelMat");
            GLint viewMatLoc = glGetUniformLocation(Render_Program, "ViewMat");
            GLint projMatLoc = glGetUniformLocation(Render_Program, "ProjectionMat");

            if (modelMatLoc != -1)
                glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            if (viewMatLoc != -1)
                glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
            if (projMatLoc != -1)
                glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

            // Bind texture (you can customize this per model if needed)
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cTextureLoader::GetInstance().Texture_01_A);

            // Render the model
            model->Render();
        }
    }

    glUseProgram(0);
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
    glUseProgram(Render_Program);

    // Send current time to shader
    GLint currentTimeLoc = glGetUniformLocation(Render_Program, "CurrentTime");
    if (currentTimeLoc != -1)
    {
        glUniform1f(currentTimeLoc, currentTime);
    }

    // Set up texture uniform
    GLint textureLoc = glGetUniformLocation(Render_Program, "Texture0");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 0); // Texture unit 0
    }
    else {
        std::cout << "No texture0 uniform location!" << std::endl;
    }
    textureLoc = glGetUniformLocation(Render_Program, "Texture1");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 1); // Texture unit 1
    }

    // Get uniform locations for tiling and flipping 
    GLint textureTilingLoc = glGetUniformLocation(Render_Program, "TextureTiling");
    GLint flipHorizontalLoc = glGetUniformLocation(Render_Program, "FlipHorizontal");

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
            glm::mat4 modelMat =    shape->getTranslationMatrix() * 
                                    shape->getRotationMatrix() * 
                                    shape->getScaleMatrix();
            // -= Camera =-
            // View Matrix
            glm::mat4 viewMat = mCamera.GetViewMat();
            // Camera's Projection Matrix
            glm::mat4 projectionMat = mCamera.GetProjectionMat();

            // Send combined model matrix to shader
            GLint QuadModelMatLoc = glGetUniformLocation(Render_Program,  "ModelMat");
            GLint viewMatLoc = glGetUniformLocation(Render_Program,       "ViewMat");
            GLint projMatLoc = glGetUniformLocation(Render_Program,       "ProjectionMat");

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

            /*std::cout << "View Matrix:\n";
            for (int i = 0; i < 4; ++i) {
                std::cout << viewMat[i][0] << " " << viewMat[i][1] << " " << viewMat[i][2] << " " << viewMat[i][3] << "\n";
            }*/

            // Render the shape
            shape->render();
        }
    }

    glUseProgram(0);
}

void Renderer::RenderSkybox()
{
    if (mSkybox)
    {
        mSkybox->Render(Skybox_Program);
    }
}
