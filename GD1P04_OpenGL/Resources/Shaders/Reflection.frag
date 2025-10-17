#version 460 core

// Inputs from Vertex Shader
in vec3 FragPosition;
in vec3 FragNormal;
in vec2 FragTexCoords;

// Uniforms
uniform vec3 CameraPosition;
uniform samplerCube Texture_Skybox;
uniform sampler2D Texture0;           // Base texture
uniform sampler2D ReflectionMap;      // Controls reflection intensity
uniform float ReflectionStrength;     // Global reflection multiplier

// Output
out vec4 FinalColor;

void main()
{
    // Normalize the normal vector
    vec3 normal = normalize(FragNormal);
    
    // Calculate view direction (from fragment to camera)
    vec3 viewDir = normalize(CameraPosition - FragPosition);
    
    // Calculate reflection direction
    vec3 reflectionDir = reflect(-viewDir, normal);
    
    // Sample the object's base texture
    vec4 objectTexture = texture(Texture0, FragTexCoords);
    
    // Sample the cubemap using the reflection direction
    vec4 reflectionTexture = texture(Texture_Skybox, reflectionDir);
    
    // Sample the reflection map (grayscale - use R channel or average RGB)
    // White = fully reflective, Black = not reflective
    float reflectionMask = texture(ReflectionMap, FragTexCoords).r;
    
    // Apply global reflection strength to the mask
    float finalReflectionAmount = reflectionMask * ReflectionStrength;
    
    // Blend the textures based on the reflection map
    FinalColor = mix(objectTexture, reflectionTexture, finalReflectionAmount);
}