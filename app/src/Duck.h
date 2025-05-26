#pragma once
#include "engine/Renderable.h"
#include <glm/gtc/random.hpp>
#include "Bspline.h"
#include "Square.h"
#include <memory>

class Duck : public Renderable<PositionNormalTextureVertexData>
{
private:
	RenderableMesh<PositionNormalTextureVertexData> GenerateMesh() override;
	unsigned int textureID;
	BSpline spline;

	glm::vec3 pos;
	glm::vec3 viewDir;
	float time = 0.f;
	std::shared_ptr<Square> water;
public:
	inline void Generate() { SaveMesh(); }
	Duck(std::shared_ptr<Square> water);
	~Duck() = default;
	glm::mat4 GetModelMatrix() const;
	void Render() const override;
	void Update();
};
