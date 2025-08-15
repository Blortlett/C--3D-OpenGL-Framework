#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <memory>
#include "ShaderLoader.h"
#include "Renderer.h"
#include "Quad.h"
#include "Hexagon.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Window variable
GLFWwindow* Window;

// Renderer and shapes
Renderer* renderer;
Hexagon* hexagon1;
Hexagon* hexagon2;

// Shader program
GLuint Program_WorldSpace;


// Hex animation params
float HexMaxScale = 1.5f;
float HexMinScale = 0.5f;
bool IsHexGrowing = true;
float HexScaleIncrement = .02f;

void InitialSetup()
{
    // Set the color of the window for when the buffer is cleared
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
    // Maps the range of the window size to NDC (-1 -> 1)
    glViewport(0, 0, 800, 800);
}

void CreateShapes()
{
    // Create renderer
    renderer = new Renderer(Program_WorldSpace);

    // Create first hexagon with gradient
    hexagon1 = new Hexagon(glm::vec3(-0.6f, -0.4f, 0.0f), glm::vec3(0.4f, 0.4f, 1.0f), 0.0f);
    hexagon1->setGradientColors(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Yellow to red
    hexagon1->initialize();
    renderer->addShape(hexagon1);

    // Create second hexagon with uniform color
    hexagon2 = new Hexagon(glm::vec3(0.6f, -0.4f, 0.0f), glm::vec3(0.35f, 0.35f, 1.0f), 30.0f);
    hexagon2->setUniformColor(glm::vec3(0.0f, 0.8f, 0.6f)); // Teal
    hexagon2->initialize();
    renderer->addShape(hexagon2);
}

void Update()
{
    glfwPollEvents();

    // Get the current time and update renderer
    float currentTime = (float)glfwGetTime();
    renderer->updateTime(currentTime);

    // Animate shapes
    if (hexagon1)
    {
        // Rotating Hexagon
        hexagon1->setRotation(currentTime * -45.0f); // Counter-rotate

        // oscillating the scale between 50% and 150 % of the original size
        if (IsHexGrowing)
        {
            // Check if grown out of bounds
            if (hexagon1->getScale().x > 1.5f || hexagon1->getScale().y > 1.5f)
            {
                IsHexGrowing = false;
            }
            else
            {
                // Grow hex
                glm::vec3 newScale = hexagon1->getScale();
                newScale.x += HexScaleIncrement;
                newScale.y += HexScaleIncrement;
                hexagon1->setScale(newScale);
            }
        }
        else // Hexagon shrinking
        {
            // Check if shrunk out of bounds
            if (hexagon1->getScale().x < 0.5f || hexagon1->getScale().y < 0.5f)
            {
                IsHexGrowing = true;
            }
            else
            {
                // Shrink hex
                glm::vec3 newScale = hexagon1->getScale();
                newScale.x -= HexScaleIncrement;
                newScale.y -= HexScaleIncrement;
                hexagon1->setScale(newScale);
            }
        }
    }

    // Move hexagon2 in a circle
    if (hexagon2)
    {
        float radius = 0.3f;
        float x = 0.6f + radius * cos(currentTime);
        float y = -0.4f + radius * sin(currentTime);
        hexagon2->setPosition(glm::vec3(x, y, 0.0f));
    }
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render all shapes using the renderer
    renderer->renderAll();

    glfwSwapBuffers(Window);
}

int main()
{
    //	-= Setup App =-
    Window = nullptr;
    // Init glfw 4.6
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // create GLFW controlled window
    Window = glfwCreateWindow(800, 800, "BigGL - Hexagon Adventure!", NULL, NULL);

    // Error Check
    if (Window == NULL)
    {
        std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
        system("pause");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window);

    // Init GLEW to populate OpenGL function pointers & error check
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW failed to initialize properly. Terminating Program." << std::endl;
        system("pause");
        glfwTerminate();
        return -1;
    }

    // Setup GL functionality
    InitialSetup();

    // -= PROGRAMS =-
    Program_WorldSpace = ShaderLoader::CreateProgram(   "Resources/Shaders/WorldSpace.vert",
                                                        "Resources/Shaders/VertexColorFade.frag");

    if (Program_WorldSpace == 0)
    {
        std::cout << "Failed to create shader program. Terminating." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Create shapes
    CreateShapes();

    //	-= Main Loop =-
    while (glfwWindowShouldClose(Window) == false)
    {
        // Update all objects and run the processes
        Update();

        // Render all the objects
        Render();
    }

    // When main loop breaks, terminate program properly
    glfwTerminate();
    return 0;
}