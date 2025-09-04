/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : main
 Description : Program start and main loop where updating/rendering takes place
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <memory>
#include "ShaderLoader.h"
#include "Renderer.h"
#include "Quad.h"
#include "Cube.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "cTextureLoader.h"
#include "Camera/cCamera.h"

// Window variable
GLFWwindow* Window;

// Renderers for different shader programs
Renderer* renderer;
Renderer* animatedRenderer;

// Shapes
Quad* QuadItem;
Quad* QuadAnimated;
Cube* Cube1;

// Shader programs
GLuint Program_Shader;
GLuint Program_Animated;

// Camera
cCamera Camera1(glm::vec2(800, 800));

void InitialSetup()
{
    // Set the color of the window for when the buffer is cleared
    glClearColor(0.01f, 0.01f, 0.05f, 1.0f); // Black
    // Maps the range of the window size to NDC (-1 -> 1)
    glViewport(0, 0, 800, 800);

    // Enable Blending. Global effect. Enables rendering texture alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable Depth Testing for 3D
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Cull mesh backfaces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT); // (BUG: Unwinding anticlockwise somehow? : Hack culling the front face)
    glFrontFace(GL_CW); // Unwind mesh Clockwise

    // DEBUG
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe
}

void CreateShapes(cCamera& _SceneCamera)
{
    // Create renderers for different shader programs
    renderer = new Renderer(Program_Shader, _SceneCamera);
    animatedRenderer = new Renderer(Program_Animated, _SceneCamera);
    
    // Static Item Quad (uses TextureMix shader)
    glm::vec3 quadPosition = glm::vec3(-0.7f, -1.0f, 0.0f);
    glm::vec3 quadScale = glm::vec3(1.0f, 1.0f, 1.0f);
    float quadRotation = 0.0f;
    QuadItem = new Quad(quadPosition, quadScale, quadRotation);
    QuadItem->initialize();
    renderer->addShape(QuadItem);
    
    // Animated Quad (uses TextureAnimate shader)
    quadPosition = glm::vec3(1.0f, 1.0f, 0.0f);
    quadScale = glm::vec3(1.0f, 1.0f, 1.0f);
    quadRotation = 0.0f;
    QuadAnimated = new Quad(quadPosition, quadScale, quadRotation);
    QuadAnimated->initialize();
    animatedRenderer->addShape(QuadAnimated);

    // Create Cube (uses TextureMix shader)
    glm::vec3 cubePosition = glm::vec3(0.2f, 0.3f, -5.0f);
    glm::vec3 cubeScale = glm::vec3(1.0f, 1.0f, 1.0f);
    float cubeRotation = 0.f;
    Cube1 = new Cube(cubePosition, cubeScale, cubeRotation);
    Cube1->initialize();
    renderer->addShape(Cube1);
}

void Update()
{
    glfwPollEvents();

    // Get the current time and update both renderers
    float currentTime = (float)glfwGetTime();
    renderer->updateTime(currentTime);
    animatedRenderer->updateTime(currentTime);

    // Animate cube
    Cube1->setRotation(Cube1->getRotation() + 1.0f, glm::vec3(0,1,.3f));

    // Oscilate camera
    Camera1.OscilateUpdate(currentTime);
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render static objects (TextureMix shader)
    renderer->renderAll();
    
    // Render animated objects (TextureAnimate shader)
    animatedRenderer->RenderAllAnimated();

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

    // -= SHADER PROGRAMS =-
    // Static texture mixing shader
    Program_Shader = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert",
                                              "Resources/Shaders/TextureMix.frag");
    
    // Animated spritesheet shader
    Program_Animated = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vert",
                                                 "Resources/Shaders/TextureAnimate.frag");
    
    if (Program_Shader == 0 || Program_Animated == 0)
    {
        std::cout << "Failed to create shader programs. Terminating." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Create Scene Camera
    //Camera1(glm::vec2(800, 800));
    
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