#pragma once
#include "engine/Renderable.h"

class Square : public Renderable<PositionColorVertexData>
{
	
private:
	static const int N = 256;
	static const float minT;
	static const float h;

	RenderableMesh<PositionColorVertexData> GenerateMesh() override;
	float heightMap[N][N];
	float prevHeightMap[N][N];
	void UpdateHeightMap();
public:
	inline void Generate() { SaveMesh(); }
	inline void Update() { UpdateHeightMap(); }
};