#version 460 core 

layout(location = 0) in vec4 inPos;
layout(location = 1) in vec2 texCoords;

out FS_IN
{
    vec3 worldPos;
    vec2 texCoords;
} o;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main()
{
    o.worldPos = vec3(inPos);
    o.texCoords = texCoords;
    gl_Position = u_projectionMatrix * u_viewMatrix * inPos;
}