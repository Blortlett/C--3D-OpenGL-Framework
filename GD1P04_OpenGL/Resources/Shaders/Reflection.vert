#version 460 core

// Vertex data interpretation
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

// Uniforms
uniform mat4 ProjectionMat;
uniform mat4 ViewMat;
uniform mat4 ModelMat;

// Outputs to Fragment Shader
out vec3 FragPosition;
out vec3 FragNormal;
out vec2 FragTexCoords;

void main() {
    // Transform position to world space
    vec4 worldPos = ModelMat * vec4(Position, 1.0f);
    FragPosition = worldPos.xyz;
    
    // Transform normal to world space (use normal matrix for non-uniform scaling)
    FragNormal = mat3(transpose(inverse(ModelMat))) * Normal;
    
    // Pass through texture coordinates
    FragTexCoords = TexCoords;
    
    // Calculate final position
    gl_Position = ProjectionMat * ViewMat * worldPos;
}