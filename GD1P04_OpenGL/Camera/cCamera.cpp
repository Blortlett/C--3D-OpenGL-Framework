#include "cCamera.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

glm::mat4 cCamera::GetProjectionMat()
{
    
    return ProjectionMat;
}

glm::mat4 cCamera::GetViewMat()
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
    // Ortho matrix
    //ProjectionMat = glm::ortho(-_WindowSize.x * 0.5f, _WindowSize.x * 0.5f, -_WindowSize.y * 0.5f, _WindowSize.y * 0.5f, 0.1f, 100.0f);
    // Perspective matrix
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
