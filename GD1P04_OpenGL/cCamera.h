/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cCamera
 Description : Base camera class for scene cameras
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#pragma once
#include <fwd.hpp>
#include <vec3.hpp>
#include <vector>
#include <ext/matrix_transform.hpp>
#include <glfw3.h>

class cCamera
{
protected:
    // Camera Variables
    glm::vec3 CameraPos = glm::vec3(0, 0, 0);
    glm::vec3 CameraLookDir = glm::vec3(0, 0, -1);
    glm::vec3 CameraUp = glm::vec3(0, 1, 0);
    glm::vec3 CameraTargetPos = glm::vec3(0, 0, 0);
    float mCameraZoom = 0.002f;

    // Matrices
    glm::mat4 ProjectionMat;
    glm::mat4 mViewMat;

    // Window reference
    GLFWwindow* mWindow;

    // Projection matrix setters
    void SetProjectionOrtho(glm::vec2 _WindowSize);
    void SetProjectionPerspec(glm::vec2 _WindowSize);

    // View matrix calculation methods
    void LookAtDirection();
    void LookAtTarget();

public:
    cCamera(glm::vec2 _WindowSize);
    virtual ~cCamera() = default;

    // Accessors
    glm::mat4& GetProjectionMat();
    glm::mat4& GetViewMat();

    // Virtual update method - override in derived classes
    virtual void Update(float _DeltaTime) = 0;
};