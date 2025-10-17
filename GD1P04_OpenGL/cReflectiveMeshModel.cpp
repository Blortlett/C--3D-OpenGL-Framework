/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cReflectiveMeshModel
 Description : cReflectiveMeshModel extends cMeshModel and contains extra data and functions to render and display a reflective mesh in a 3D scene.
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#include "cReflectiveMeshModel.h"
#include "cCamera.h"
#include "cSkybox.h"
#include <iostream>

cReflectiveMeshModel::cReflectiveMeshModel(std::string _FilePath, cCamera* _Camera,
    cSkybox* _Skybox, glm::vec3 _Position, glm::vec3 _Scale, float _RotationAngle)
    : cMeshModel(_FilePath, _Position, _Scale, _RotationAngle)
    , mCamera(_Camera)
    , mSkybox(_Skybox)
{
    if (!mCamera)
    {
        std::cout << "Warning: cReflectiveMeshModel created with null camera!" << std::endl;
    }
    if (!mSkybox)
    {
        std::cout << "Warning: cReflectiveMeshModel created with null skybox!" << std::endl;
    }
}

void cReflectiveMeshModel::Update(float _DeltaTime)
{
    // Call base class update
    cMeshModel::Update(_DeltaTime);
}

void cReflectiveMeshModel::Render()
{
    // Call base class render
    cMeshModel::Render();
}