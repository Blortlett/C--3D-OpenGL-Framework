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
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        WSweight += 1;
    }
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
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
        return true;
    }

    return false;
}

int cInputSystem::Get_Key2()
{
    if (glfwGetKey(mWindow, GLFW_KEY_2) == GLFW_PRESS)
    {
        return true;
    }

    return false;
}

int cInputSystem::Get_Key3()
{
    if (glfwGetKey(mWindow, GLFW_KEY_3) == GLFW_PRESS)
    {
        return true;
    }

    return false;
}

glm::fvec2 cInputSystem::GetMousePosition()
{
    return glm::fvec2();
}
