#pragma once
#include <glm.hpp>
#include <map>

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

    // functions for getting Keyboard input (call each frame)
    glm::ivec2 Get_WASD();
    int Get_QE();
    int Get_Key1();
    int Get_Key2();
    int Get_Key3();
    bool GetMouseButton();

    // Get screenspace mouse position
    glm::fvec2 GetMousePosition();


private:
    bool isKey1Held = false;
    bool isKey2Held = false;
    bool isKey3Held = false;

    // Private constructor to prevent instantiation
    cInputSystem() {}
    GLFWwindow* mWindow = nullptr;

    bool IsKeyPressedOnce(int key);

};