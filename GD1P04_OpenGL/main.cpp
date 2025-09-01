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
#include "Camera/cCamera.h"

// Window variable
GLFWwindow* Window;

// Renderer and shapes
Renderer* renderer;
Quad* Quad1;

// Shader program
GLuint Program_Shader;



void InitialSetup()
{
    // Set the color of the window for when the buffer is cleared
    glClearColor(0.01f, 0.01f, 0.05f, 1.0f); // Black
    // Maps the range of the window size to NDC (-1 -> 1)
    glViewport(0, 0, 800, 800);

    // Enable Blending. Global effect. Enables rendering texture alpha
    glEnable(GL_BLEND);
    //glDisable(GL_DEPTH_TEST); // DEBUG
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CreateShapes(cCamera _SceneCamera)
{
    // Create renderer
    renderer = new Renderer(Program_Shader, _SceneCamera);
    
    // Create Quad
    glm::vec3 quadPosition = glm::vec3(400.0f, 0.0f, 0.0f);
    glm::vec3 quadScale = glm::vec3(8000.0f, 1000.0f, 1.0f); // 8,1,1
    float quadRotation = 0.0f;
    Quad1 = new Quad(quadPosition, quadScale, quadRotation);
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
    Window = glfwCreateWindow(800, 800, "BigGL - Camera Adventure!", NULL, NULL);

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
    Program_Shader = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert",
                                              "Resources/Shaders/Texture.frag");
    
    if (Program_Shader == 0)
    {
        std::cout << "Failed to create shader program. Terminating." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Load Texture
    cTextureLoader::GetInstance().LoadTexture("Lancer-Walk02.png");
    cTextureLoader::GetInstance().LoadTexture("Elite Orc-Walk.png");

    // Create Scene Camera
    cCamera Camera1(glm::vec2(800, 800));
    
    // Create shapes
    CreateShapes(Camera1);

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