/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : Hexagon
 Description : Extends base class: Shape. Stores information and functionality required to render a hex
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/


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

    void initialize();
};


