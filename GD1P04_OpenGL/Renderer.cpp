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
    std::cout << "Rendering " << meshModels.size() << " mesh models" << std::endl;

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
            std::cout << "Rendering model at program: " << Render_Program << std::endl;

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

void Renderer::RenderSkybox()
{
    if (mSkybox)
    {
        mSkybox->Render(Skybox_Program);
    }
}
