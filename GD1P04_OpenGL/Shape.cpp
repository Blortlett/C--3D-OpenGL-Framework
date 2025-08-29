#include "Shape.h"
#include <gtc/type_ptr.hpp>

Shape::Shape(glm::vec3 pos, glm::vec3 scl, float rotAngle)
    : position(pos), scale(scl), rotationAngle(rotAngle), rotationAxis(0.0f, 0.0f, 1.0f)
{
    VAO = VBO = EBO = 0;
    translationMat = glm::mat4(1.0f);
    rotationMat = glm::mat4(1.0f);
    scaleMat = glm::mat4(1.0f);
}

Shape::~Shape()
{
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);
    if (VBO != 0) glDeleteBuffers(1, &VBO);
    if (EBO != 0) glDeleteBuffers(1, &EBO);
}

void Shape::setupBuffers()
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
    // Position attribute (location = 0)                                    // 8 was 6
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)                                       // 8 was 6
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Texture attribute (Location = 2) // Tutorial time: 49:30
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Shape::setPosition(glm::vec3 pos)
{
    position = pos;
}

void Shape::setScale(glm::vec3 scl)
{
    scale = scl;
}

void Shape::setRotation(float angle, glm::vec3 axis)
{
    rotationAngle = angle;
    rotationAxis = axis;
}

void Shape::updateTransforms()
{
    translationMat = glm::translate(glm::mat4(1.0f), position);
    rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), rotationAxis);
    scaleMat = glm::scale(glm::mat4(1.0f), scale);
}

void Shape::render()
{
    bind();

    if (!indices.empty())
    {
        glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(vertices.size() / 6)); // 6 components per vertex
    }

    unbind();
}

void Shape::bind()
{
    glBindVertexArray(VAO);
}

void Shape::unbind()
{
    glBindVertexArray(0);
}

void Shape::shareVAO(const Shape* other)
{
    if (!other) return;

    // Clean up shape's own buffers if they exist
    if (VAO != 0 && VAO != other->VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO != 0 && VBO != other->VBO) glDeleteBuffers(1, &VBO);
    if (EBO != 0 && EBO != other->EBO) glDeleteBuffers(1, &EBO);

    // Share the other shape's buffers
    VAO = other->VAO;
    VBO = other->VBO;
    EBO = other->EBO;

    // Copy the vertex and index data for consistency
    vertices = other->vertices;
    indices = other->indices;
}

void Shape::regenerate()
{
    // Clean up existing buffers
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);
    if (VBO != 0) glDeleteBuffers(1, &VBO);
    if (EBO != 0) glDeleteBuffers(1, &EBO);

    // Clear existing data
    vertices.clear();
    indices.clear();

    // Generate new vertices
    generateVertices();

    // Setup new buffers
    setupBuffers();
}