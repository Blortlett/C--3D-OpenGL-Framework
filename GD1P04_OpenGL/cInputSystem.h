#pragma once
#include <glm.hpp>

class GLFWwindow;

class cInputSystem {
public:
    // Get the singleton instance
    static cInputSystem& GetInstance() {
        static cInputSystem instance;
        return instance;
    }
    // Delete copy constructor and assignment operator to prevent copying
    cInputSystem(const cInputSystem&) = delete;
    cInputSystem& operator=(const cInputSystem&) = delete;

    // Add window when program first starts
    void SetWindow(GLFWwindow* _Window) { mWindow = _Window; }

    // Get WASD input call each frame
    glm::ivec2 Get_WASD();
private:
    // Private constructor to prevent instantiation
    cInputSystem() {}
    GLFWwindow* mWindow = nullptr;

};