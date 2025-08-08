#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Window variable
GLFWwindow* Window;

// ColorFade Porgram container
GLuint Program_ColorFade;
GLuint Program_WorldSpace;

// VAO and VBO for quad
GLuint VBO_Quad;
GLuint VAO_Quad;
GLuint EBO_Quad;

// Program vars
float CurrentTime;

// Vertices for second quad (top-right, using triangle strip)
GLfloat Vertices_Quad[] = {
	// Position         // Color
	 -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	 -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	  0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f,
	  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f
};

GLuint Indices_Quad[] = {
	0, 1, 2,
	0, 2, 3,
};

// -= Quad Transform =-
// Quad Position
glm::vec3 QuadPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::mat4 TranslationMat;
// Quad Rotation
float QuadRotationAngle = 45.0f;
glm::mat4 RotationMat;
// Quad Scale
glm::vec3 QuadScale = glm::vec3(0.5f, 0.5f, 1.0f);
glm::mat4 ScaleMat;

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

	// Calculate Model Matrix
	TranslationMat = glm::translate(glm::mat4(1.0f), QuadPosition);
	// Calculate Rotation Matrix
	RotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(QuadRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	// Calculate Scale Matrix
	ScaleMat = glm::scale(glm::mat4(1.0f), QuadScale);
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the program and VAO
	glUseProgram(Program_WorldSpace);
	glBindVertexArray(VAO_Quad);

	// Send variables to the shaders via Uniform
	GLint CurrentTimeLoc = glGetUniformLocation(Program_WorldSpace, "CurrentTime");
	glUniform1f(CurrentTimeLoc, CurrentTime);
	// Worldspace Transform
	// Position
	GLint TranslationMatLoc = glGetUniformLocation(Program_WorldSpace, "TranslationMat");
	glUniformMatrix4fv(TranslationMatLoc, 1, GL_FALSE, glm::value_ptr(TranslationMat));
	// Rotation
	GLint RotationMatLoc = glGetUniformLocation(Program_WorldSpace, "RotationMat");
	glUniformMatrix4fv(RotationMatLoc, 1, GL_FALSE, glm::value_ptr(RotationMat));
	// Scale
	GLint ScaleMatLoc = glGetUniformLocation(Program_WorldSpace, "ScaleMat");
	glUniformMatrix4fv(ScaleMatLoc, 1, GL_FALSE, glm::value_ptr(ScaleMat));
	// You could combine all matrices and pass the combination to the shader (ie combine with cpu pass one matrix to gpu) 
	// e.g.:
	//QuadModelMat = TranslationMat * RotationMat * ScaleMat;
	// TODO ^^



	// Render quad
	glBindVertexArray(VAO_Quad);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	Window = glfwCreateWindow(800, 800, "BigGL", NULL, NULL);


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
	Program_WorldSpace = ShaderLoader::CreateProgram(		"Resources/Shaders/WorldSpace.vert",
															"Resources/Shaders/VertexColorFade.frag");


	// -= Setup second quad =-
	// 1) Generate the VAO for the second quad
	glGenVertexArrays(1, &VAO_Quad);
	glBindVertexArray(VAO_Quad);

	// 2) Generate the EBO for the second quad
	glGenBuffers(1, &EBO_Quad);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Quad);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices_Quad), Indices_Quad, GL_STATIC_DRAW);

	// 3) Generate the VBO for the second quad
	glGenBuffers(1, &VBO_Quad);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Quad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Quad), Vertices_Quad, GL_STATIC_DRAW);

	// 4) Set the Vertex Attribute information (same format as first quad)
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