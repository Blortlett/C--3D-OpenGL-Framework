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
#include "cReflectiveMeshModel.h"
#include "Quad.h"
#include "Cube.h"
#include "cSkybox.h"
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
// Reflective Mesh Model
cReflectiveMeshModel* ReflectiveModel;

// Shader programs
GLuint Program_Shader;
GLuint Program_Reflection;
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
    // Create renderers for different shader programs
    renderer = new Renderer(Program_Shader, Program_Skybox, _SceneCamera);

    // Set the reflection program
    renderer->setReflectionProgram(Program_Reflection);

    // Check if cubemap texture is loaded
    GLuint cubemapID = cTextureLoader::GetInstance().Cubemap_Texture;
    std::cout << "Cubemap Texture ID from loader: " << cubemapID << std::endl;

    if (cubemapID == 0)
    {
        std::cout << "ERROR: Cubemap texture not loaded! Make sure cTextureLoader loads the cubemap." << std::endl;
    }

    // Create and add skybox
    cSkybox* skybox = new cSkybox(&Camera1, cubemapID);
    renderer->setSkybox(skybox);

    // Create and add a mesh model from OBJ file
    glm::vec3 modelPosition = glm::vec3(1.f, -1.f, -1.f);
    glm::vec3 modelScale = glm::vec3(1.f, 1.f, 1.f);
    float modelRotation = 0.0f;

    // Load Seaweed
    MyModel = new cMeshModel("Resources/Models/SM_Env_Seaweed_01.obj",
        modelPosition, modelScale, modelRotation);
    renderer->addMeshModel(MyModel);

    // Load Chalice (reflective)
    modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    ReflectiveModel = new cReflectiveMeshModel("Resources/Models/SM_Item_Chalice_01.obj",
        &Camera1, renderer->getSkybox(), modelPosition, modelScale, modelRotation);
    renderer->addReflectiveMeshModel(ReflectiveModel);


    // Additional debug
    std::cout << "Skybox set in renderer" << std::endl;
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

    // Render mesh models first
    renderer->RenderAllMeshModels();
    renderer->RenderAllReflectiveMeshModels();

    // Render skybox last
    renderer->RenderSkybox();

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
    // Texture shader
    Program_Shader = ShaderLoader::CreateProgram(       "Resources/Shaders/ClipSpace.vert",
                                                        "Resources/Shaders/Texture.frag");
    // Reflection shader
    Program_Reflection = ShaderLoader::CreateProgram(   "Resources/Shaders/Reflection.vert",
                                                        "Resources/Shaders/Reflection.frag");
    // Skybox Shader
    Program_Skybox = ShaderLoader::CreateProgram(       "Resources/Shaders/Skybox.vert",
                                                        "Resources/Shaders/Skybox.frag");
    
    
    if (Program_Shader == 0 || Program_Skybox == 0 || Program_Reflection == 0)
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