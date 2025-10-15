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
