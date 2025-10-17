#version 460 core;

vec3 Normal = normalize(FragNormal);
vec3 ViewDir = normalize(FragPos - CameraPos)
vec3 ReflectDir = reflect(ViewDir, Normal);