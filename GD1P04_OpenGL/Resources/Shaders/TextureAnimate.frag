#version 460 core

// Inputs from Vertex Shader
in vec3 FragColor;
in vec2 FragTexCoords;

// Animation inputs
uniform sampler2D AnimatedTexture;
uniform float CurrentTime;
uniform vec2 SheetSize;
uniform float AnimSpeed;
uniform int TotalFrames;

// Output
out vec4 FinalColor;

void main()
{
    // Calculate current frame based on time
    int currentFrame = int(floor(CurrentTime * AnimSpeed)) % TotalFrames;

    // Calculate frame position in the grid
    int frameX = currentFrame % int(SheetSize.x);
    int frameY = currentFrame / int(SheetSize.x);

    // Calculate frame size in UV coordinates
    vec2 frameSize = vec2(1.0 / SheetSize.x, 1.0 / SheetSize.y);

    // Calculate UV offset for current frame
    vec2 frameOffset = vec2(float(frameX) * frameSize.x, float(frameY) * frameSize.y);

    // Scale and offset texture coordinates to sample correct frame
    vec2 animatedUV = FragTexCoords * frameSize + frameOffset;

    // Sample the texture with animated UV coordinates
    //FinalColor = vec4(1, 0, 0, 1);
    FinalColor = texture(AnimatedTexture, animatedUV);
}