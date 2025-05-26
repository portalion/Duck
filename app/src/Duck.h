#pragma once
#include "engine/Renderable.h"

class Duck : public Renderable<PositionNormalTextureVertexData>
{
private:
	RenderableMesh<PositionNormalTextureVertexData> GenerateMesh() override;
	unsigned int textureID;
public:
	inline void Generate() { SaveMesh(); }
	~Duck() = default;
	glm::mat4 GetModelMatrix() const;
	void Render() const override;
};