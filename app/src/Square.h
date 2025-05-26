#pragma once
#include "engine/Renderable.h"

class Square : public Renderable<PositionColorVertexData>
{
protected:
	RenderableMesh<PositionColorVertexData> GenerateMesh() override
	{
		RenderableMesh<PositionColorVertexData> mesh;
		mesh.vertices = {
			{ { -1.f, -1.f, -0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  1.f, -1.f, -0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { -1.f,  1.f, -0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  1.f,  1.f, -0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }
		};
		mesh.indices = { 0, 1, 2, 2, 1, 3 };
		return mesh;
	}
public:
	inline void Generate() { SaveMesh(); }
};