#pragma once
#include "Cube.h"
#include <string>
#include "cCamera.h"

class cSkybox
{
private:
	Cube mSkyCube;
	cCamera* mCamera;
	glm::vec3 mPosition;

public:
	cSkybox(cCamera* _Camera, std::string _Filepaths[6]);

	void Render(GLuint _Skybox_Program);
};