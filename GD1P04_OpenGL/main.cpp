#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"

void Render(GLFWwindow* _Window, GLuint _Program_FixedTri)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(_Program_FixedTri);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);

	glfwSwapBuffers(_Window);
}

void Update()
{
	glfwPollEvents();
}

int main()
{
	//	-= Setup App =-
	GLFWwindow* Window = nullptr;
	// Init glfw 4.6
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// InitialSetup()
	// Setup GL functionality
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	// create GLFW controlled window
	Window = glfwCreateWindow(800, 800, "First OpenGL Window", NULL, NULL);


	// Error Check
	if (Window == NULL)
	{
		std::cout << "GLFW failted to initialize properly. Terminating program." << std::endl;
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

	
	GLuint Program_FixedTri = ShaderLoader::CreateProgram(	"Resources/Shaders/FixedTriangle.vert",
															"Resources/Shaders/FixedColor.frag");
	
	//	-= Main Loop =-
	while (glfwWindowShouldClose(Window) == false)
	{
		// Update all objects and run the processes
		Update();

		// Render all the objects
		Render(Window, Program_FixedTri);
	}

	// When main loop breaks, terminate program properly
	glfwTerminate();
	return 0;
}