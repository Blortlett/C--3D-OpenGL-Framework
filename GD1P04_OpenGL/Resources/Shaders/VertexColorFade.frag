#version 460 core

in vec3 FragColor;
uniform float CurrentTime;
uniform vec3 BlendColor; // The solid color to blend with

out vec4 FinalColor;

void main()
{
    // Oscillating mix ratio using the sine wave (0.0 to 1.0)
    float mixRatio = (sin(CurrentTime * 2.0) + 1.0) * 0.5;
    
    // Blend the original color with the blend color
    vec3 blendedColor = mix(FragColor, BlendColor, mixRatio);
    
    // Apply the original fade effect
    FinalColor = vec4(blendedColor, 0.f);
}