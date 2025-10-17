#version 460 core

// Inputs from Vertex Shader
in vec3 FragPosition;
in vec3 FragNormal;
in vec2 FragTexCoords;

// Uniforms
uniform vec3 CameraPosition;
uniform samplerCube Texture_Skybox;
uniform sampler2D Texture0;  // Add the object's base texture
uniform float ReflectionStrength;  // Optional: control blend amount

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
    
    // Sample the object's base texture
    vec4 objectTexture = texture(Texture0, FragTexCoords);
    
    // Sample the cubemap using the reflection direction
    vec4 reflectionTexture = texture(Texture_Skybox, reflectionDir);
    
    // Blend the textures (0.5 = 50/50 mix)
    // You can also use ReflectionStrength uniform for dynamic control
    FinalColor = mix(objectTexture, reflectionTexture, 0.5f);
}