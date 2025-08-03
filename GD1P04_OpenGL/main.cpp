#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"


// New variables
GLuint Program_PositionOnly;
GLuint VBO_Tri;
GLuint VAO_Tri;

// Verticies
GLfloat Verticies_Tri[] = {
	// Position
	 0.0f, 0.0f, 0.0f,
	-0.5f, 0.8f, 0.0f,
	 0.5f, 0.8f, 0.0f,
};

void InitialSetup()
{
	// Set the color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	// Maps the range of the window size to NDC (-1 -> 1)
	glViewport(0, 0, 800, 800);
}


void Render(GLFWwindow* _Window, GLuint _Program)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(_Program);
	glBindVertexArray(VAO_Tri);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
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

	// Setup GL functionality
	InitialSetup();
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

	// -= FIRST PROGRAM =-
	//GLuint Program_FixedTri = ShaderLoader::CreateProgram(	"Resources/Shaders/FixedTriangle.vert",
	//															"Resources/Shaders/FixedColor.frag");
	// Add vertex attribute setup here
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	// -= SECOND PROGRAM =-
	Program_PositionOnly = ShaderLoader::CreateProgram(		"Resources/Shaders/PositionOnly.vert",
															"Resources/Shaders/FixedColor.frag");
	// 1) Generate the VAO for a triangle
	glGenVertexArrays(1, &VAO_Tri);
	glBindVertexArray(VAO_Tri);
	
	// 2) Generate the VBO for a Triangle
	glGenBuffers(1, &VBO_Tri);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Tri);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verticies_Tri), Verticies_Tri, GL_STATIC_DRAW);

	// 3) Set the Vertex Attribute information (how to interpret the vertex data)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//	-= Main Loop =-
	while (glfwWindowShouldClose(Window) == false)
	{
		// Update all objects and run the processes
		Update();

		// Render all the objects
		Render(Window, Program_PositionOnly);
	}

	// When main loop breaks, terminate program properly
	glfwTerminate();
	return 0;
}