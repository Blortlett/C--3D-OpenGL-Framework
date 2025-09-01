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

    glm::mat4 ProjectionMat;
    glm::mat4 mViewMat;
    
public:
    cCamera(glm::vec2 _WindowSize);

    void LookAtDirection();
    void LookAtTarget();
    glm::mat4 GetProjectionMat();
    glm::mat4 GetViewMat();

    
    glm::vec3 CameraTargetPos = glm::vec3(0, 0, 0);
};
