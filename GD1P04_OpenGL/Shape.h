#pragma once
#include <glew.h>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Shape
{
protected:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    // Transform properties
    glm::vec3 position;
    glm::vec3 scale;
    float rotationAngle;
    glm::vec3 rotationAxis;

    // Transform matrices
    glm::mat4 translationMat;
    glm::mat4 rotationMat;
    glm::mat4 scaleMat;

    // OpenGL setup
    virtual void setupBuffers();
    virtual void generateVertices() = 0; // Pure virtual - each shape defines its own vertices

public:
    Shape(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), float rotAngle = 0.0f);
    virtual ~Shape();

    // Transform methods
    void setPosition(glm::vec3 pos);
    void setScale(glm::vec3 scl);
    void setRotation(float angle, glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getScale() const { return scale; }
    float getRotation() const { return rotationAngle; }

    // Matrix getters
    glm::mat4 getTranslationMatrix() const { return translationMat; }
    glm::mat4 getRotationMatrix() const { return rotationMat; }
    glm::mat4 getScaleMatrix() const { return scaleMat; }

    // Update transform matrices
    virtual void updateTransforms();

    // Render methods
    virtual void render();
    void bind();
    void unbind();
    void shareVAO(const Shape* other);

    // Utility
    virtual void regenerate(); // Regenerate vertices and buffers
};