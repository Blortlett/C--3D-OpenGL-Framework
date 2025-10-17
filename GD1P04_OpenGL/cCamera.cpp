/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cCamera
 Description : Stores information and functionality required to calculate a scene camera
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


#include "cCamera.h"

#include <ext/matrix_clip_space.hpp>

#include <iostream>

glm::mat4& cCamera::GetProjectionMat()
{
    
    return ProjectionMat;
}

glm::mat4& cCamera::GetViewMat()
{
    return mViewMat;
}

cCamera::cCamera(glm::vec2 _WindowSize)
{
    // Init View Matrix - Default Camera View
    CameraPos = glm::vec3(0, 0, 3);
    CameraLookDir = glm::vec3(0, 0, -1);
    CameraTargetPos = glm::vec3(0, 0, 0);
    CameraUp = glm::vec3(0, 1, 0);
    LookAtTarget();

    // Init Projection Matrix
    SetProjectionPerspec(_WindowSize);
}



void cCamera::SetProjectionOrtho(glm::vec2 _WindowSize)
{
    ProjectionMat = glm::ortho(-_WindowSize.x * mCameraZoom, _WindowSize.x * mCameraZoom, -_WindowSize.y * mCameraZoom, _WindowSize.y * mCameraZoom, 0.1f, 100.0f);
}

void cCamera::SetProjectionPerspec(glm::vec2 _WindowSize)
{
    ProjectionMat = glm::perspective(glm::radians(45.0f), (float)_WindowSize.x / (float)_WindowSize.y, 0.1f, 100.0f);
}

void cCamera::LookAtDirection()
{
    // Calculate view matrix
    mViewMat = glm::lookAt(CameraPos, CameraPos + CameraLookDir, CameraUp);
}

void cCamera::LookAtTarget()
{
    // Calculate view matrix
    mViewMat = glm::lookAt(CameraPos, CameraTargetPos, CameraUp);
}
