#include "Renderer.h"

Renderer::Renderer(GLuint program) : shaderProgram(program), currentTime(0.0f)
{
}

Renderer::~Renderer()
{
    clearShapes();
}

void Renderer::addShape(Shape* shape)
{
    if (shape)
    {
        shapes.push_back(shape);
    }
}

void Renderer::removeShape(Shape* shape)
{
    shapes.erase(std::remove(shapes.begin(), shapes.end(), shape), shapes.end());
}

void Renderer::clearShapes()
{
    shapes.clear();
}

void Renderer::updateTime(float time)
{
    currentTime = time;
}

void Renderer::renderAll()
{
    if (shaderProgram == 0) return;

    glUseProgram(shaderProgram);

    // Send current time to shader
    GLint currentTimeLoc = glGetUniformLocation(shaderProgram, "CurrentTime");
    if (currentTimeLoc != -1)
    {
        glUniform1f(currentTimeLoc, currentTime);
    }

    // Send blend color to shader
    GLint blendColorLoc = glGetUniformLocation(shaderProgram, "BlendColor");
    if (blendColorLoc != -1)
    {
        glUniform3f(blendColorLoc, 0.0f, 1.0f, 1.0f); // Send this colour (Cyan)
    }

    // Set up texture uniform
    GLint textureLoc = glGetUniformLocation(shaderProgram, "Texture0");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 0); // Texture unit 0
    }
    textureLoc = glGetUniformLocation(shaderProgram, "Texture1");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 1); // Texture unit 1
    }

    // Render all shapes
    for (auto& shape : shapes)
    {
        if (shape)
        {
            // Update transforms
            shape->updateTransforms();

            // Calculate combined model matrix: Scale * Rotation * Translation
            // Note: OpenGL matrices are applied in reverse order
            glm::mat4 modelMat = shape->getTranslationMatrix() * 
                               shape->getRotationMatrix() * 
                               shape->getScaleMatrix();

            // Send combined model matrix to shader
            GLint modelMatLoc = glGetUniformLocation(shaderProgram, "ModelMat");
            if (modelMatLoc != -1)
            {
                glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            }


            // Render the shape
            shape->render();
        }
    }

    glUseProgram(0);
}