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
	vec4 pos = VP * vec4(Position, 1.0f);
	// Set z = w so that after perspective divide, z/w = 1.0 (maximum depth)
	gl_Position = pos.xyww;
	FragTexCoords = vec3(Position.xyz);
}