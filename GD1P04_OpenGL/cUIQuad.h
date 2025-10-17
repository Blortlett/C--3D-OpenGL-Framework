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

#pragma once
#include "Quad.h"
#include <glm.hpp>

class cUIQuad
{
private:
    Quad* quad;

    // Screen space position and size (in pixels)
    glm::vec2 screenPosition;
    glm::vec2 screenSize;

    // Textures
    GLuint currentTexture;
    GLuint normalTexture;
    GLuint hoverTexture;

    // State
    bool isHovered;
    bool wasClicked;

    // Matrices
    glm::mat4 orthoProjectionMat;

public:
    cUIQuad(glm::vec2 screenPos, glm::vec2 quadSize, GLuint normalTex, GLuint hoverTex);
    ~cUIQuad();

    // Update methods
    void UpdateOrthoProjection(glm::vec2 windowSize);
    void CheckHover(glm::vec2 mousePos, glm::vec2 windowSize);
    bool CheckClick(glm::vec2 mousePos, glm::vec2 windowSize, bool mouseButtonPressed);

    // Render in screen space
    void Render(GLuint program);

    // Getters
    bool GetIsHovered() const { return isHovered; }
    GLuint GetCurrentTexture() const { return currentTexture; }
};