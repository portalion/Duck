#pragma once
#include "engine/Renderable.h"

class Square : public Renderable<PositionTextureVertexData>
{
private:
	static const int N = 256;
	static const float minT;
	static const float h;

	unsigned int heightTextureID;
	unsigned int cubeTextureID;

	RenderableMesh<PositionTextureVertexData> GenerateMesh() override;
	float heightMap[N][N];
	float prevHeightMap[N][N];
	float d[N][N];
	void MakeRain();
	void UpdateHeightMap();
	glm::vec3 CalculateNormal(int x, int y);
public:
	Square(unsigned int t);
	inline void Generate() { SaveMesh(); }
	void BumpHeightMap(float x, float y);
	void Update();
	void Render() const override;
};