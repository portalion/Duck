#pragma once
#include "engine/Renderable.h"

class Cube : public Renderable<PositionNormalCubeTextureVertexData>
{
protected:
	unsigned int textureID;

    RenderableMesh<PositionNormalCubeTextureVertexData> GenerateMesh() override;
public:
    Cube(std::vector<std::string> faces);
    void Render() const override;
};