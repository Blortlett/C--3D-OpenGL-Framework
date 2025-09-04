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


#pragma once
#include <fwd.hpp>
#include <vec3.hpp>
#include <vector>
#include <ext/matrix_transform.hpp>

class cCamera
{
private:
    // Camera Variables
    glm::vec3 CameraPos = glm::vec3(0, 0, 3);
    glm::vec3 CameraLookDir = glm::vec3(0, 0, -1);
    glm::vec3 CameraUp = glm::vec3(0, 1, 0);
    float mCameraZoom = 0.002f;

    glm::mat4 ProjectionMat;
    glm::mat4 mViewMat;
    
    // Set camera projection matrix
    void SetProjectionOrtho(glm::vec2 _WindowSize);
    void SetProjectionPerspec(glm::vec2 _WindowSize);

    // Set camera look at
    void LookAtDirection();
    void LookAtTarget();

public:
    cCamera(glm::vec2 _WindowSize);



    glm::mat4& GetProjectionMat();
    glm::mat4& GetViewMat();

    // Oscilate for project brief
    void OscilateUpdate(float _DeltaTime);

    
    glm::vec3 CameraTargetPos = glm::vec3(0, 0, 0);
};
