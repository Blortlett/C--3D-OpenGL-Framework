/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cOscilatingCamera
 Description : cOscilatingCamera extends cCamera and contains extra functions to rotate the camera around an origin point, while looking at this origin point
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#pragma once
#include "cCamera.h"
#include "cInputSystem.h"

class cOrbitalCamera: public cCamera
{
private:
    float mOrbitAngle = 0.0f;
    float mOrbitRadius = 4.0f;
    float mOrbitHeight = 0.0f;
    float mMoveSpeed = 0.001f;

public:
    cOrbitalCamera(glm::vec2 _Resolution)
    : cCamera(_Resolution)
    { }

    void Update(float _DeltaTime)
    {
        glm::ivec2 moveInput = cInputSystem::GetInstance().Get_WASD();
        mOrbitAngle += moveInput.x * _DeltaTime * mMoveSpeed;

        CameraPos.x = sin(mOrbitAngle) * mOrbitRadius;
        CameraPos.y = mOrbitHeight;
        CameraPos.z = cos(mOrbitAngle) * mOrbitRadius;
        LookAtTarget();
    }
};