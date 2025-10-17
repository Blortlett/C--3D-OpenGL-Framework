/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : Quad
 Description : Extends base class: Shape. Stores information and functionality required to render a Quad
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


#include "Quad.h"
#include <iostream>

Quad::Quad(glm::vec3 pos, glm::vec3 scl, float rotAngle)
    : Shape(pos, scl, rotAngle)
{
    // Default colors
    color1 = glm::vec3(1.0f, 0.0f, 0.0f); // Red
    color2 = glm::vec3(0.0f, 1.0f, 0.0f); // Green
    color3 = glm::vec3(1.0f, 0.0f, 1.0f); // Magenta
    color4 = glm::vec3(0.0f, 1.0f, 1.0f); // Cyan
}

void Quad::generateVertices()
{
    // Vertices for quad (Position + Color)
    vertices = {
        // Position             // Color                        // Texture Coords
        -0.5f,  0.5f, 0.0f,     color1.r, color1.g, color1.b,   0.0f, 1.0f,     // Top-left
        -0.5f, -0.5f, 0.0f,     color2.r, color2.g, color2.b,   0.0f, 0.0f,     // Bottom-left
         0.5f, -0.5f, 0.0f,     color3.r, color3.g, color3.b,   1.0f, 0.0f,     // Bottom-right
         0.5f,  0.5f, 0.0f,     color4.r, color4.g, color4.b,   1.0f, 1.0f,     // Top-right
    };

    // Indices for two triangles
    indices = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };
}

void Quad::setColors(glm::vec3 c1, glm::vec3 c2, glm::vec3 c3, glm::vec3 c4)
{
    color1 = c1;
    color2 = c2;
    color3 = c3;
    color4 = c4;
}

void Quad::setUniformColor(glm::vec3 color)
{
    color1 = color2 = color3 = color4 = color;
}

void Quad::initialize()
{
    generateVertices();
    setupBuffers();
}

void Quad::render()
{
    bind();

    // Don't bind any textures here - let the caller handle texture binding
    // This allows cUIQuad to control which texture is used

    if (!indices.empty())
    {
        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        // Ensure vertices is not empty to avoid division by zero or invalid access
        if (!vertices.empty())
        {
            glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(vertices.size() / 8)); // 8 floats per vertex
        }
        else
        {
            std::cout << "Error: No vertices to render!" << std::endl;
        }
    }

    unbind();
}