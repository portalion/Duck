#pragma once
#include "engine/Renderable.h"

class Duck : public Renderable<PositionNormalTextureVertexData>
{
private:
	RenderableMesh<PositionNormalTextureVertexData> GenerateMesh() override;

public:
	inline void Generate() { SaveMesh(); }
	~Duck() = default;
};