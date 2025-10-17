/************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c)
 2024 Media Design School
 File Name : VertexStandard.h
 Description : This structure allows me to store and use vertex data in a structured manner
 Author : Matthew Bartlett
 Mail : Matthew.Bartlett@mds.ac.nz
 ************************************************/

#pragma once
#include <glm.hpp>

struct VertexStandard
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;

	VertexStandard()
	{
		position = glm::vec3(0.0f);
		normal = glm::vec3(0.0f);
		texcoord = glm::vec3(0.0f);
	};
	VertexStandard(glm::vec3 pos, glm::vec2 texc, glm::vec3 normal = glm::vec3(0.0f))
	{
		position = pos;
		texcoord = texc;
	}
};