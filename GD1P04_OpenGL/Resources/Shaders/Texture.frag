#version 460 core

// Inputs from Vertex Shader
in vec3 FragColor;
in vec2 FragTexCoords;

// Uniform Inputs
uniform sampler2D Texture0;

// Output
out vec4 FinalColor;

void main()
{
    FinalColor = vec4(1, 0, 0, 1);//texture(Texture0, FragTexCoords); // * vec4(FragColor, 1.0f);
    FinalColor = texture(Texture0, FragTexCoords); // * vec4(FragColor, 1.0f);
}