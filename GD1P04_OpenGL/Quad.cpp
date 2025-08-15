#include "Quad.h"

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
        // Position         // Color
        -0.5f,  0.5f, 0.0f,  color1.r, color1.g, color1.b, // Top-left
        -0.5f, -0.5f, 0.0f,  color2.r, color2.g, color2.b, // Bottom-left
         0.5f, -0.5f, 0.0f,  color3.r, color3.g, color3.b, // Bottom-right
         0.5f,  0.5f, 0.0f,  color4.r, color4.g, color4.b  // Top-right
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