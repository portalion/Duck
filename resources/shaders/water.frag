#version 460 core

in FS_IN
{
    vec3 worldPos;
    vec2 texCoords;
} i;

out vec4 FragColor;

uniform sampler2D u_Texture;

uniform vec3 lightPos = vec3(0.f, -10.f, 0.f);     // World-space light position
uniform vec3 viewPos;      // Camera position
uniform vec3 lightColor = vec3(1.f, 1.f, 1.f);
uniform vec3 objectColor = vec3(0.2f, 0.2f, 0.5f);

void main()
{
    vec3 norm = normalize(texture(u_Texture, i.texCoords).rgb);

    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 lightDir = normalize(lightPos - i.worldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - i.worldPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    //FragColor = texture(u_Texture, i.texCoords);
    FragColor = vec4(result, 1.0);
}
