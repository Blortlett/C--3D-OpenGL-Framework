#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"

// Window variable
GLFWwindow* Window;

// ColorFade Porgram container
GLuint Program_ColorFade;

// VAO and VBO for first tri/quad
GLuint VBO_Tri;
GLuint VAO_Tri;

// VAO and VBO for second quad
GLuint VBO_Quad;
GLuint VAO_Quad;

// Program vars
float CurrentTime;

// Verticies
GLfloat Verticies_Quad[] = {
	// -= First Triangle
	// Position			// Color
	 0.0f, -0.8f, 0.0f,	1.0f, 0.0f, 0.0f,
	-0.5f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
	 0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
	 // Second Triangle
	// Position			// Color
	 0.0f, 0.8f, 0.0f,	0.75f, 0.0f, 1.0f,
	-0.5f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
	 0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
};

// Vertices for second quad (top-right, using triangle strip)
GLfloat Vertices_Quad[] = {
	// Position         // Color
	 0.0f, 0.4f, 0.0f,  1.0f, 0.0f, 0.0f,
	 0.0f, 0.8f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, 0.4f, 0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, 0.8f, 0.0f,  1.0f, 0.0f, 1.0f 
};

void InitialSetup()
{
	// Set the color of the window for when the buffer is cleared
	//glClearColor(0.3f, 0.0f, 1.0f, 1.0f); // Purple
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
	// Maps the range of the window size to NDC (-1 -> 1)
	glViewport(0, 0, 800, 800);
}

void Update()
{
	glfwPollEvents();

	// Get the current time
	CurrentTime = (float)glfwGetTime();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the program and VAO
	glUseProgram(Program_ColorFade);
	glBindVertexArray(VAO_Tri);

	// Send variables to the shaders via Uniform
	GLint CurrentTimeLoc = glGetUniformLocation(Program_ColorFade, "CurrentTime");
	glUniform1f(CurrentTimeLoc, CurrentTime);

	// Render First Quad
	// Render the first triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// Render the second triangle
	glDrawArrays(GL_TRIANGLES, 3, 3);

	// Render second quad
	glBindVertexArray(VAO_Quad);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Unbind asstets to prevent accidental use/modification
	glBindVertexArray(0);
	glUseProgram(0);

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

	// Setup GL functionality
	InitialSetup();

	// -= PROGRAMS =-
	Program_ColorFade = ShaderLoader::CreateProgram(		"Resources/Shaders/PositionOnly.vert",
															"Resources/Shaders/VertexColorFade.frag");

	// -= Setup first Tri/Quad
	// 1) Generate the VAO for a triangle
	glGenVertexArrays(1, &VAO_Tri);
	glBindVertexArray(VAO_Tri);
	
	// 2) Generate the VBO for a Triangle
	glGenBuffers(1, &VBO_Tri);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Tri);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verticies_Quad), Verticies_Quad, GL_STATIC_DRAW);

	// 3) Set the Vertex Attribute information (how to interpret the vertex data)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind VAO for first tri
	glBindVertexArray(0);

	// -= Setup second quad =-
	// 1) Generate the VAO for the second quad
	glGenVertexArrays(1, &VAO_Quad);
	glBindVertexArray(VAO_Quad);

	// 2) Generate the VBO for the second quad
	glGenBuffers(1, &VBO_Quad);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Quad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Quad), Vertices_Quad, GL_STATIC_DRAW);

	// 3) Set the Vertex Attribute information (same format as first quad)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind VAO for second quad
	glBindVertexArray(0);

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