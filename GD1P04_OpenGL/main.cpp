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
#include "cMeshModel.h"
#include "Quad.h"
#include "Cube.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "cInputSystem.h"
#include "cTextureLoader.h"
#include "cOrbitalCamera.h"

// Window variable
GLFWwindow* Window;

// Renderers for different shader programs
Renderer* renderer;
//Renderer* animatedRenderer;

// Shapes
Quad* QuadItem;
Quad* QuadAnimated;
Cube* Cube1;
// Mesh Model
cMeshModel* MyModel;

// Shader programs
GLuint Program_Shader;
GLuint Program_Skybox;

// Camera
cOrbitalCamera Camera1(glm::vec2(800, 800));

void InitialSetup()
{
    // Set the color of the window for when the buffer is cleared
    glClearColor(0.49f, 0.5f, 0.51f, 1.0f); // MidGrey
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
    cTextureLoader::GetInstance().LoadCubemap("Skybox");


    // Create renderers for different shader programs
    renderer = new Renderer(Program_Shader, Program_Skybox, _SceneCamera);
    //animatedRenderer = new Renderer(Program_Animated, _SceneCamera);

    // Create and add a mesh model from OBJ file
    glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 modelScale = glm::vec3(1.f, 1.f, 1.f);
    float modelRotation = 0.0f;

    MyModel = new cMeshModel("Resources/Models/SM_Item_Chalice_01.obj",
        modelPosition, modelScale, modelRotation);
    renderer->addMeshModel(MyModel);
}

void Update()
{
    glfwPollEvents();

    // Get the current time and update both renderers
    float currentTime = (float)glfwGetTime();
    renderer->updateTime(currentTime);
    //animatedRenderer->updateTime(currentTime);

    // Update camera
    Camera1.Update(currentTime);
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render mesh models
    renderer->RenderAllMeshModels();

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
    cInputSystem::GetInstance().SetWindow(Window);

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
    Program_Shader = ShaderLoader::CreateProgram(   "Resources/Shaders/ClipSpace.vert",
                                                    "Resources/Shaders/Texture.frag");
    Program_Skybox = ShaderLoader::CreateProgram(   "Resources/Shaders/",
                                                    "Resources/Shaders/"); // TODO: Add the shader .vert n .frag
    
    
    if (Program_Shader == 0 || Program_Skybox == 0)
    {
        std::cout << "Failed to create shader programs. Terminating." << std::endl;
        glfwTerminate();
        return -1;
    }
    
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