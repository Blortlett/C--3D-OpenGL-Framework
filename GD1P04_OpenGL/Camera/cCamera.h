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

    glm::vec2 GetWindowSize();
    glm::mat4 GetProjectionMat();
    
public:
    cCamera();

    void LookAtDirection();
    void LookAtTarget();

    
    glm::vec3 CameraTargetPos = glm::vec3(0, 0, 0);
};
