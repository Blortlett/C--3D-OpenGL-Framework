#version 460 core

// Inputs from Vertex Shader
in vec3 FragColor;
in vec2 FragTexCoords;

// Uniform Inputs
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform float CurrentTime;

// Output
out vec4 FinalColor;

void main()
{
    // Blend factor
    float blendFactor = (sin(CurrentTime * 2.0) + 1.0) * 0.5;
    
    // Mix texture based on Blend Factor
    FinalColor = mix(texture(Texture0, FragTexCoords), texture(Texture1, FragTexCoords), blendFactor);
}