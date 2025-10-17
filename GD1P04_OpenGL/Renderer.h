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
#include <glew.h>
#include <vector>
#include "Shape.h"
#include "cMeshModel.h"
#include "cReflectiveMeshModel.h"
#include "cUIQuad.h"

class cCamera;
class cSkybox;

class Renderer
{
public:
    Renderer(GLuint& _Program, GLuint& _Skybox_Program, cCamera& _Camera);
    ~Renderer();

    // Shape management
    void addShape(Shape* shape);
    void removeShape(Shape* shape);
    void clearShapes();

    // Regular mesh model management
    void addMeshModel(cMeshModel* model);
    void removeMeshModel(cMeshModel* model);
    void clearMeshModels();

    // Reflective mesh model management
    void addReflectiveMeshModel(cReflectiveMeshModel* model);
    void removeReflectiveMeshModel(cReflectiveMeshModel* model);
    void clearReflectiveMeshModels();

    // Rendering
    void renderAll();
    void RenderAllMeshModels();
    void RenderAllReflectiveMeshModels();
    void RenderSkybox();

    // Time update
    void updateTime(float time);

    // Skybox management
    void setSkybox(cSkybox* skybox) { mSkybox = skybox; }
    cSkybox* getSkybox() const { return mSkybox; }

    // Reflection shader program setter
    void setReflectionProgram(GLuint _Program) { Reflection_Program = _Program; }

    // // UI methods
    void SetUIQuad(cUIQuad* uiQuad) { mUIQuad = uiQuad; }
    void RenderUI();
    void UpdateUI(glm::vec2 mousePos, glm::vec2 windowSize, bool mouseButtonPressed);

    // Texture swap
    void ToggleAlternateTexture() { mUseAlternateTexture = !mUseAlternateTexture; }
    bool IsUsingAlternateTexture() const { return mUseAlternateTexture; }

private:
    GLuint& Render_Program;
    GLuint& Skybox_Program;
    GLuint Reflection_Program;

    float currentTime;
    cCamera& mCamera;
    cSkybox* mSkybox;

    std::vector<Shape*> shapes;
    std::vector<cMeshModel*> meshModels;
    std::vector<cReflectiveMeshModel*> reflectiveMeshModels;
    cUIQuad* mUIQuad;


    bool mUseAlternateTexture;
};