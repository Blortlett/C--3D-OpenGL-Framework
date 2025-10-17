#version 460 core

// Inputs from Vertex Shader
in vec3 FragPosition;
in vec3 FragNormal;
in vec2 FragTexCoords;

// Uniforms
uniform vec3 CameraPosition;
uniform samplerCube Texture_Skybox;

// Output
out vec4 FinalColor;

void main()
{
    // Normalize the normal vector
    vec3 normal = normalize(FragNormal);
    
    // Calculate view direction (from fragment to camera)
    vec3 viewDir = normalize(CameraPosition - FragPosition);
    
    // Calculate reflection direction
    // reflect() expects incident vector (from camera to fragment), so negate viewDir
    vec3 reflectionDir = reflect(-viewDir, normal);
    
    // Sample the cubemap using the reflection direction
    vec3 reflectionColor = texture(Texture_Skybox, reflectionDir).rgb;
    
    // Output the reflection color
    FinalColor = vec4(reflectionColor, 1.0);
}