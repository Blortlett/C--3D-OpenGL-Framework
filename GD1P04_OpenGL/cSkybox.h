/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cSkybox
 Description : cSkybox contains data and functions to render and display a skybox in a 3D scene.
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#pragma once
#include "cSkyCube.h"
#include <string>
#include "cCamera.h"
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include <iostream>

class cSkybox
{
private:
	cSkyCube mSkyCube;
	cCamera* mCamera;
	GLuint mCubemapTexture;

	int mIndiciesCount;
	int mVerticiesCount;

public:
	cSkybox(cCamera* _Camera, GLuint _CubemapTexture);

	void Render(GLuint _Skybox_Program);

	// Accessors if needed
	cSkyCube& GetSkyCube() { return mSkyCube; }
};