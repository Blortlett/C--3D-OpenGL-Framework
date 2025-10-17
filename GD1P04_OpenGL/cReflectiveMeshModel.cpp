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

    // Add any reflective-specific update logic here if needed
}

void cReflectiveMeshModel::Render()
{
    // The actual rendering is still done by calling the base class render
    // But this method exists so the Renderer can set up reflection-specific uniforms
    // before calling this render method

    cMeshModel::Render();
}