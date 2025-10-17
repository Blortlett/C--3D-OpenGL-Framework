/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : Cube
 Description : Extends base class: Shape. Stores information and functionality required to render a cube
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


#include "Cube.h"

Cube::Cube(glm::vec3 pos, glm::vec3 scl, float rotAngle)
	: Shape(pos, scl, rotAngle)
{

}

void Cube::generateVertices()
{
    // Vertices for cube (Position + Color)
    vertices = {
        // Position             // Texture Coords
        // Front Quad
        -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f,

        // Back Quad
         0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,

        // Right Quad
         0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f,

        // Left Quad
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     1.0f, 1.0f,

         // Top Quad
         -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,     1.0f, 1.0f,

          // Bottom Quad
         -0.5f, -0.5f,  0.5f,     0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,     1.0f, 1.0f,
    };

    // Indices for two triangles
    indices = {
        0, 1, 2,    // Front tri 1
        0, 2, 3,    // Front tri 2
        4, 5, 6,    // Back tri 1
        4, 6, 7,    // Back tri 2
        8, 9, 10,   // Right tri 1
        8, 10, 11,  // Right tri 2
        12, 13, 14, // Left tri 1
        12, 14, 15, // Left tri 2
        16, 17, 18, // Top tri 1
        16, 18, 19, // Top tri 2
        20, 21, 22, // Bottom tri 1
        20, 22, 23, // Bottom tri 2
    };
}

void Cube::setupBuffers()
{
    // Generate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and setup EBO
    if (!indices.empty())
    {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
            &indices[0], GL_STATIC_DRAW);
    }

    // Generate and setup VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
        &vertices[0], GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Texture attribute (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cube::initialize()
{
    generateVertices();
    setupBuffers();
}
