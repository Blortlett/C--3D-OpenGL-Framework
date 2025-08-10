#pragma once
#include "Shape.h"
#include <cmath>

class Hexagon : public Shape
{
private:
    glm::vec3 centerColor;
    glm::vec3 edgeColor;
    bool useGradient;

protected:
    void generateVertices() override;

public:
    Hexagon(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), float rotAngle = 0.0f);

    // Set colors
    void setUniformColor(glm::vec3 color);
    void setGradientColors(glm::vec3 center, glm::vec3 edge);

    // Initialize the hexagon (call this after setting properties)
    void initialize();
};

// Implementation
Hexagon::Hexagon(glm::vec3 pos, glm::vec3 scl, float rotAngle)
    : Shape(pos, scl, rotAngle), useGradient(true)
{
    centerColor = glm::vec3(1.0f, 1.0f, 1.0f); // White center
    edgeColor = glm::vec3(0.0f, 0.5f, 1.0f);   // Blue edge
}

void Hexagon::generateVertices()
{
    const float PI = 3.14159265359f;
    const int sides = 6;

    // Clear existing data
    vertices.clear();
    indices.clear();

    // Add center vertex
    vertices.insert(vertices.end(), {
        0.0f, 0.0f, 0.0f,  // Position (center)
        centerColor.r, centerColor.g, centerColor.b  // Color
        });

    // Add edge vertices
    for (int i = 0; i < sides; ++i)
    {
        float angle = (2.0f * PI * i) / sides;
        float x = 0.5f * cos(angle);  // 0.5f radius
        float y = 0.5f * sin(angle);

        glm::vec3 vertexColor = useGradient ? edgeColor : centerColor;

        vertices.insert(vertices.end(), {
            x, y, 0.0f,  // Position
            vertexColor.r, vertexColor.g, vertexColor.b  // Color
            });
    }

    // Create triangles from center to each edge
    for (int i = 1; i <= sides; ++i)
    {
        indices.insert(indices.end(), {
            0,  // Center vertex
            (GLuint)i,  // Current edge vertex
            (GLuint)(i == sides ? 1 : i + 1)  // Next edge vertex (wrap around)
            });
    }
}

void Hexagon::setUniformColor(glm::vec3 color)
{
    centerColor = edgeColor = color;
    useGradient = false;
}

void Hexagon::setGradientColors(glm::vec3 center, glm::vec3 edge)
{
    centerColor = center;
    edgeColor = edge;
    useGradient = true;
}

void Hexagon::initialize()
{
    generateVertices();
    setupBuffers();
}