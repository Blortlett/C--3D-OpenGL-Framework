#pragma once

#pragma once
#include "Shape.h"
#include <string>


class cCamera;

class cSkyCube : public Shape
{
protected:
	void generateVertices() override;
	void setupBuffers() override;

	

public:
	cSkyCube();


};

