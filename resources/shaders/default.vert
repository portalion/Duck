#version 460 core

layout(location = 0) in vec4 i_position;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec3 i_texCoords;

layout(location = 0) out vec3 o_texCoords;

uniform mat4 u_modelMatrix = mat4(1.0);
uniform mat4 u_viewMatrix = mat4(1.0);
uniform mat4 u_projectionMatrix = mat4(1.0);

void main()
{
    o_texCoords = i_texCoords;
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * i_position;
};