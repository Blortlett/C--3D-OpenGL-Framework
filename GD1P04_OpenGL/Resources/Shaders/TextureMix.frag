#version 460 core

// Inputs from Vertex Shader
in vec3 FragColor;
in vec2 FragTexCoords;

// Uniform Inputs
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform float CurrentTime;

// New uniforms for tiling and flipping
uniform vec2 TextureTiling;
uniform bool FlipHorizontal;

// Output
out vec4 FinalColor;

void main()
{
    // Apply tiling and flipping to texture coordinates
    vec2 modifiedTexCoord = FragTexCoords * TextureTiling;
    
    // Apply horizontal flip if enabled
    if (FlipHorizontal && modifiedTexCoord.y > 1.0) {
        modifiedTexCoord.x = TextureTiling.x - modifiedTexCoord.x;
    }
    
    // Blend factor
    float blendFactor = (sin(CurrentTime * 2.0) + 1.0) * 0.5;
    
    // Mix texture based on Blend Factor using modified coordinates
    FinalColor = mix(texture(Texture0, modifiedTexCoord), texture(Texture1, modifiedTexCoord), blendFactor);
}