#include "Cube.h"
#include "Texture.h"

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

Cube::Cube(std::vector<std::string> faces)
{
	textureID = LoadCubemap(faces);
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
