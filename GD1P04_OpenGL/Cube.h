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

