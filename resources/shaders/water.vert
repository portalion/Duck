#version 460 core 

layout(location = 0) in vec4 inPos;

out FS_IN
{
    vec3 worldPos;
    vec3 normal;
    vec2 texCoords;
} o;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

uniform float a;

void main()
{
    o.worldPos = vec3(inPos);
    o.texCoords = (inPos.xz + a / 2.0f) / a;
    o.normal = vec3(0.0f, -1.0f, 0.0f); // Assuming a flat water surface
    gl_Position = u_projectionMatrix * u_viewMatrix * inPos;
}