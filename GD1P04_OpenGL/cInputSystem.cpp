/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cInputSystem
 Description : This class creates a singleton object for any part of the codebase to easily interperate user input
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#include "cInputSystem.h"
#include <glfw3.h>

glm::ivec2 cInputSystem::Get_WASD()
{
    // Get Left/Right component for vector
    int ADweight = 0;
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        ADweight -= 1;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        ADweight += 1;
    }

    // Get Forward/Backward component for vector
	int WSweight = 0;
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        WSweight += 1;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        WSweight -= 1;
    }

	return glm::ivec2(ADweight, WSweight);
}

int cInputSystem::Get_QE()
{
    // Get Forward/Backward component for vector
    int QEweight = 0;
    if (glfwGetKey(mWindow, GLFW_KEY_E) == GLFW_PRESS)
    {
        QEweight += 1;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_Q) == GLFW_PRESS)
    {
        QEweight -= 1;
    }

    return QEweight;
}

int cInputSystem::Get_Key1()
{
    if (glfwGetKey(mWindow, GLFW_KEY_1) == GLFW_PRESS)
    {
        return IsKeyPressedOnce(1);
    }
    else
    {
        isKey1Held = false;
    }

    return false;
}

int cInputSystem::Get_Key2()
{
    if (glfwGetKey(mWindow, GLFW_KEY_2) == GLFW_PRESS)
    {
        return IsKeyPressedOnce(2);
    }
    else
    {
        isKey2Held = false;
    }

    return false;
}

int cInputSystem::Get_Key3()
{
    if (glfwGetKey(mWindow, GLFW_KEY_3) == GLFW_PRESS)
    {
        return IsKeyPressedOnce(3);
    }
    else
    {
        isKey3Held = false;
    }

    return false;
}

glm::fvec2 cInputSystem::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(mWindow, &xpos, &ypos);
    return glm::fvec2(static_cast<float>(xpos), static_cast<float>(ypos));
}

bool cInputSystem::GetMouseButton()
{
    return glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool cInputSystem::IsKeyPressedOnce(int _Key)
{
    switch (_Key)
    {
    case 1:
    {
        if (!isKey1Held)
        {
            isKey1Held = true;
            return true;
        }
        return false;
    }
    case 2:
    {
        if (!isKey2Held)
        {
            isKey2Held = true;
            return true;
        }
        return false;
    }
    case 3:
    {
        if (!isKey3Held)
        {
            isKey3Held = true;
            return true;
        }
        return false;
    }
    }

    return false;
}
