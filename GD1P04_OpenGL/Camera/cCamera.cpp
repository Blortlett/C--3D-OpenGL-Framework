#include "cCamera.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>


glm::vec2 cCamera::GetWindowSize()
{
    glm::vec2 windowSize = glm::vec2(GetWindowSize().x, GetWindowSize().y);
    return windowSize;
}

glm::mat4 cCamera::GetProjectionMat()
{
    glm::vec2 windowSize = GetWindowSize();
    glm::mat4 projectionMatrix;
    projectionMatrix = glm::ortho(windowSize.x * 0.5f, windowSize.x * 0.5f, -windowSize.y * 0.5f, windowSize.y * 0.5f, 0.1f, 100.0f);
    return projectionMatrix;
}

cCamera::cCamera()
{
    CameraPos = glm::vec3(0, 0, 3);
    CameraLookDir = glm::vec3(0, 0, -1);
    CameraTargetPos = glm::vec3(0, 0, 0);
    CameraUp = glm::vec3(0, 1, 0);

    
}

void cCamera::LookAtDirection()
{
    // Calculate view matrix
    glm::mat4 ViewMat = glm::lookAt(CameraPos, CameraPos + CameraLookDir, CameraUp);
}

void cCamera::LookAtTarget()
{
    // Calculate view matrix
    glm::mat4 ViewMat = glm::lookAt(CameraPos, CameraTargetPos, CameraUp);
}
