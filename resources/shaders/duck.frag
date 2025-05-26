#version 460 core

layout(location = 0) in vec2 i_texCoords;

layout(location = 0) out vec4 FragColor;

uniform sampler2D  u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, i_texCoords);
    FragColor = texColor;
}