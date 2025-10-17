/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cUIQuad
 Description : Extends base class: Quad. Stores information and functionality required to render a Quad in ortho projection to be used as UI
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#include "cUIQuad.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

cUIQuad::cUIQuad(glm::vec2 screenPos, glm::vec2 quadSize, GLuint normalTex, GLuint hoverTex)
    : screenPosition(screenPos)
    , screenSize(quadSize)
    , normalTexture(normalTex)
    , hoverTexture(hoverTex)
    , currentTexture(hoverTex)
    , isHovered(false)
    , wasClicked(false)
{
    // Create a quad at origin with scale of 1,1,1
    quad = new Quad(glm::vec3(0.0f), glm::vec3(1.0f), 0.0f);
    quad->setUniformColor(glm::vec3(1.0f, 1.0f, 1.0f));
    quad->initialize();
}

cUIQuad::~cUIQuad()
{
    delete quad;
}

void cUIQuad::UpdateOrthoProjection(glm::vec2 windowSize)
{
    // Create orthographic projection from 0,0 (bottom-left) to windowSize (top-right)
    orthoProjectionMat = glm::ortho(0.0f, windowSize.x, 0.0f, windowSize.y, -1.0f, 1.0f);
}

void cUIQuad::CheckHover(glm::vec2 mousePos, glm::vec2 windowSize)
{
    // Convert mouse Y from top-left origin to bottom-left origin
    float adjustedMouseY = windowSize.y - mousePos.y;

    bool wasHovered = isHovered;

    // Check if mouse is within quad bounds
    isHovered = (mousePos.x >= screenPosition.x &&
        mousePos.x <= screenPosition.x + screenSize.x &&
        adjustedMouseY >= screenPosition.y &&
        adjustedMouseY <= screenPosition.y + screenSize.y);

    // Update texture based on hover state
    if (isHovered)
    {
        currentTexture = hoverTexture;
    }
    else
    {
        currentTexture = normalTexture;
    }
}

bool cUIQuad::CheckClick(glm::vec2 mousePos, glm::vec2 windowSize, bool mouseButtonPressed)
{
    // First check if hovering
    CheckHover(mousePos, windowSize);

    // Detect click (button pressed while hovering and wasn't clicked last frame)
    if (isHovered && mouseButtonPressed && !wasClicked)
    {
        wasClicked = true;
        return true;
    }

    // Reset clicked state when button released
    if (!mouseButtonPressed)
    {
        wasClicked = false;
    }

    return false;
}

void cUIQuad::Render(GLuint program)
{
    glUseProgram(program);

    // Set position and scale for the quad in screen space
    quad->setPosition(glm::vec3(screenPosition.x + screenSize.x * 0.5f,
        screenPosition.y + screenSize.y * 0.5f,
        0.0f));
    quad->setScale(glm::vec3(screenSize.x, screenSize.y, 1.0f));
    quad->updateTransforms();

    // Create model matrix
    glm::mat4 modelMat = quad->getTranslationMatrix() *
        quad->getRotationMatrix() *
        quad->getScaleMatrix();

    // Identity view matrix for screen space rendering
    glm::mat4 viewMat = glm::mat4(1.0f);

    // Send matrices to shader
    GLint modelMatLoc = glGetUniformLocation(program, "ModelMat");
    GLint viewMatLoc = glGetUniformLocation(program, "ViewMat");
    GLint projMatLoc = glGetUniformLocation(program, "ProjectionMat");

    if (modelMatLoc != -1)
        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    if (viewMatLoc != -1)
        glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    if (projMatLoc != -1)
        glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(orthoProjectionMat));

    // Set texture uniform
    GLint textureLoc = glGetUniformLocation(program, "Texture0");
    if (textureLoc != -1)
    {
        glUniform1i(textureLoc, 0);
    }

    // Disable texture tiling for UI
    GLint textureTilingLoc = glGetUniformLocation(program, "TextureTiling");
    if (textureTilingLoc != -1)
    {
        glUniform2f(textureTilingLoc, 1.0f, 1.0f);
    }

    GLint flipHorizontalLoc = glGetUniformLocation(program, "FlipHorizontal");
    if (flipHorizontalLoc != -1)
    {
        glUniform1i(flipHorizontalLoc, GL_FALSE);
    }

    // Bind the current texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentTexture);

    // Render the quad
    quad->render();

    glUseProgram(0);
}