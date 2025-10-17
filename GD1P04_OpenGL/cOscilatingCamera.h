/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : cOscilatingCamera
 Description : cOscilatingCamera extends cCamera and contains extra functions to rotate the camera around an origin point, while looking at this origin point
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#pragma once
#include "cCamera.h"

class cOscilatingCamera : public cCamera
{
public:
    cOscilatingCamera(glm::vec2 _Resolution)
        : cCamera(_Resolution)
    {
    }

    void Update(float _CurrentTime)
	{
        // Oscillation parameters
        const float amplitudeX = .3f;
        const float frequency = 1.0f;

        // Calculate oscillation offset using sin function
        float offsetX = amplitudeX * sin(frequency * _CurrentTime);

        // Set camera position
        CameraPos.x = CameraTargetPos.x + offsetX;
        LookAtDirection();
	}
};