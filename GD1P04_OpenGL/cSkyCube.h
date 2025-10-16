#pragma once
#include "Shape.h"
#include <string>

class cCamera;

class cSkyCube : public Shape
{
protected:
    void generateVertices() override
    {
        // Vertices for cube - ONLY positions (3 floats per vertex)
        // For cubemap sampling, we use the position as the texture coordinate
        vertices = {
            // Front Face
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,

             // Back Face
              1.0f,  1.0f, -1.0f,
              1.0f, -1.0f, -1.0f,
             -1.0f, -1.0f, -1.0f,
             -1.0f,  1.0f, -1.0f,

             // Right Face
              1.0f,  1.0f,  1.0f,
              1.0f, -1.0f,  1.0f,
              1.0f, -1.0f, -1.0f,
              1.0f,  1.0f, -1.0f,

              // Left Face
              -1.0f,  1.0f, -1.0f,
              -1.0f, -1.0f, -1.0f,
              -1.0f, -1.0f,  1.0f,
              -1.0f,  1.0f,  1.0f,

              // Top Face
              -1.0f,  1.0f, -1.0f,
              -1.0f,  1.0f,  1.0f,
               1.0f,  1.0f,  1.0f,
               1.0f,  1.0f, -1.0f,

               // Bottom Face
               -1.0f, -1.0f,  1.0f,
               -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f,  1.0f,
        };

        // Indices for two triangles per face
        indices = {
            // Bottom
            20, 22, 23,
            20, 21, 22,
            // Top
            16, 18, 19,
            16, 17, 18,
            // Left
            12, 14, 15,
            12, 13, 14,
            // Right
            8, 10, 11,
            8, 9, 10,
            // Back
            4, 6, 7,
            4, 5, 6,
            // Front
            0, 2, 3,
            0, 1, 2,
        };
    }

    void setupBuffers() override
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
        // ONLY Position attribute (location = 0) - 3 floats per vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

public:
    cSkyCube()
        : Shape(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), 0.f)
    {
        generateVertices();
        setupBuffers();
    }
};