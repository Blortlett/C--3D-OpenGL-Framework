#version 460 core

// Vertex Data Interpretation
layout (location = 0) in vec3 Position;

// Inputs
uniform mat4 VP;

// Outputs to fragment shader
out vec3 FragTexCoords;

// Shader Functionality
void main()
{
	gl_Position = VP * vec4(Position, 1.0f);
	FragTexCoords = vec3(Position.xyz);
}