#version 460 core

// Uniform Inputs
uniform samplerCube Texture_Skybox;

// Inputs from the Vertex shader
in vec3 FragTexCoords;

// Output
out vec4 FinalColor;

void main()
{
	FinalColor = texture(Texture_Skybox, FragTexCoords);
}