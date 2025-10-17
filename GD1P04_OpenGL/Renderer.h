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
#include "cMeshModel.h"

class cSkybox;
class cCamera;

class Renderer
{
private:
    std::vector<Shape*> shapes;
    std::vector<cMeshModel*> meshModels;
    GLuint& Render_Program;
    GLuint& Skybox_Program;
    float currentTime;

    cCamera& mCamera;

    cSkybox* mSkybox;

public:
    Renderer(GLuint& _Program,GLuint& _Skybox_Program, cCamera& _Camera);
    ~Renderer();

    // Shape management
    void addShape(Shape* shape);
    void removeShape(Shape* shape);
    void clearShapes();

    // Mesh models Management
    void addMeshModel(cMeshModel* model);
    void removeMeshModel(cMeshModel* model);
    void clearMeshModels();

    // Rendering
    void updateTime(float time);
    void RenderSkybox();
    void RenderAllMeshModels();

    // Skybox
    void setSkybox(cSkybox* skybox)
    {
        mSkybox = skybox;
    }
};