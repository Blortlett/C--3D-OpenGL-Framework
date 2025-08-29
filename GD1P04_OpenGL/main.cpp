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

#include "cTextureLoader.h"

// Window variable
GLFWwindow* Window;

// Renderer and shapes
Renderer* renderer;
Quad* Quad1;

// Shader program
GLuint Program_WorldSpace;
GLuint Program_Texture;

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

    // Load Texture
    cTextureLoader::GetInstance().LoadTexture("Lancer-Walk02.png");
    
    // Create Quad
    Quad1 = new Quad(glm::vec3(-0.6f, -0.4f, 0.0f), glm::vec3(0.4f, 0.4f, 1.0f), 0.0f);
    Quad1->initialize();
    renderer->addShape(Quad1);
}

void Update()
{
    glfwPollEvents();

    // Get the current time and update renderer
    float currentTime = (float)glfwGetTime();
    renderer->updateTime(currentTime);
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
    Program_WorldSpace = ShaderLoader::CreateProgram("Resources/Shaders/Texture.vert",
                                              "Resources/Shaders/Texture.frag");
    
    if (Program_WorldSpace == 0)
    {
        std::cout << "Failed to create world space shader program. Terminating." << std::endl;
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