/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : Cube
 Description : Extends base class: Shape. Stores information and functionality required to render a cube
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#pragma once
#include "Shape.h"

class Cube: public Shape
{
protected:
	void generateVertices() override;
	void setupBuffers() override;

public: 
	Cube(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), float rotAngle = 0.0f);

	// Initialize the quad
	void initialize();
};

