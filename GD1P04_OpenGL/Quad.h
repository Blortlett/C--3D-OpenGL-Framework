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


#pragma once
#include "Shape.h"

class Quad : public Shape
{
private:
    glm::vec3 color1, color2, color3, color4; // Colors for each vertex

protected:
    void generateVertices() override;

public:
    Quad(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), float rotAngle = 0.0f);

    void render() override;

    // Set colors for vertices
    void setColors(glm::vec3 c1, glm::vec3 c2, glm::vec3 c3, glm::vec3 c4);
    void setUniformColor(glm::vec3 color);

    // Initialize the quad
    void initialize();
};