#version 460 core

layout(location = 0) in vec3 i_texCoords;

layout(location = 0) out vec4 FragColor;

uniform samplerCube  u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, i_texCoords);
    FragColor = texColor;
}