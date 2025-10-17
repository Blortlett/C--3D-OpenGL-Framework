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

#pragma once
#include "cMeshModel.h"

class cCamera;
class cSkybox;

class cReflectiveMeshModel : public cMeshModel
{
public:
    cReflectiveMeshModel(std::string _FilePath, cCamera* _Camera, cSkybox* _Skybox,
        glm::vec3 _Position = glm::vec3(0.0f),
        glm::vec3 _Scale = glm::vec3(1.0f),
        float _RotationAngle = 0.0f);

    void Render() override;
    void Update(float _DeltaTime) override;

    // Setters for camera and skybox (in case you need to change them)
    void SetCamera(cCamera* _Camera) { mCamera = _Camera; }
    void SetSkybox(cSkybox* _Skybox) { mSkybox = _Skybox; }

    // Getters
    cCamera* GetCamera() const { return mCamera; }
    cSkybox* GetSkybox() const { return mSkybox; }

private:
    cCamera* mCamera;
    cSkybox* mSkybox;

    glm::vec3 Normal;
    glm::vec3 ViewDir;
    glm::vec3 ReflectDir;
};