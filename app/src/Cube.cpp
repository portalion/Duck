#include "Cube.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

RenderableMesh<PositionNormalCubeTextureVertexData> Cube::GenerateMesh()
{
    RenderableMesh<PositionNormalCubeTextureVertexData> mesh;
    mesh.vertices = {
        { { -1, -1,  1, 1 }, {  0,  0, -1 }, { -1, -1,  1 } },
        { {  1, -1,  1, 1 }, {  0,  0, -1 }, {  1, -1,  1 } },
        { {  1,  1,  1, 1 }, {  0,  0, -1 }, {  1,  1,  1 } },
        { { -1,  1,  1, 1 }, {  0,  0, -1 }, { -1,  1,  1 } },

        // Back (-Z)
        { { -1, -1, -1, 1 }, {  0,  0,  1 }, { -1, -1, -1 } },
        { {  1, -1, -1, 1 }, {  0,  0,  1 }, {  1, -1, -1 } },
        { {  1,  1, -1, 1 }, {  0,  0,  1 }, {  1,  1, -1 } },
        { { -1,  1, -1, 1 }, {  0,  0,  1 }, { -1,  1, -1 } },

        // Left (-X)
        { { -1, -1, -1, 1 }, {  1,  0,  0 }, { -1, -1, -1 } },
        { { -1, -1,  1, 1 }, {  1,  0,  0 }, { -1, -1,  1 } },
        { { -1,  1,  1, 1 }, {  1,  0,  0 }, { -1,  1,  1 } },
        { { -1,  1, -1, 1 }, {  1,  0,  0 }, { -1,  1, -1 } },

        // Right (+X)
        { {  1, -1,  1, 1 }, { -1,  0,  0 }, {  1, -1,  1 } },
        { {  1, -1, -1, 1 }, { -1,  0,  0 }, {  1, -1, -1 } },
        { {  1,  1, -1, 1 }, { -1,  0,  0 }, {  1,  1, -1 } },
        { {  1,  1,  1, 1 }, { -1,  0,  0 }, {  1,  1,  1 } },

        // Top (+Y)
        { { -1,  1,  1, 1 }, {  0, -1,  0 }, { -1,  1,  1 } },
        { {  1,  1,  1, 1 }, {  0, -1,  0 }, {  1,  1,  1 } },
        { {  1,  1, -1, 1 }, {  0, -1,  0 }, {  1,  1, -1 } },
        { { -1,  1, -1, 1 }, {  0, -1,  0 }, { -1,  1, -1 } },

        // Bottom (-Y)
        { { -1, -1, -1, 1 }, {  0,  1,  0 }, { -1, -1, -1 } },
        { {  1, -1, -1, 1 }, {  0,  1,  0 }, {  1, -1, -1 } },
        { {  1, -1,  1, 1 }, {  0,  1,  0 }, {  1, -1,  1 } },
        { { -1, -1,  1, 1 }, {  0,  1,  0 }, { -1, -1,  1 } },
    };
    mesh.indices = {
         0, 2, 1, 0, 3, 2,
         // Back
         4, 5, 6, 4, 6, 7,
         // Left
         8, 10, 9, 8, 11, 10,
         // Right
         12, 14, 13, 12, 15, 14,
         // Top
         16, 18, 17, 16, 19, 18,
         // Bottom
         20, 22, 21, 20, 23, 22
    };
    return mesh;
}

unsigned int Cube::LoadCubemap(std::vector<std::string> faces)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

Cube::Cube(std::vector<std::string> faces)
{
	LoadCubemap(faces);
    SaveMesh();
}

void Cube::Render() const
{
    glDepthMask(GL_FALSE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    renderer.Render(renderingMode);
    glDepthMask(GL_TRUE);
}
