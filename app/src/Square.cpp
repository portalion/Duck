#include "Square.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const float Square::h = 2.f / static_cast<float>(N - 1);
const float Square::minT = 1.f/ static_cast<float>(N - 1);

RenderableMesh<PositionColorVertexData> Square::GenerateMesh()
{
	RenderableMesh<PositionColorVertexData> mesh;
	mesh.vertices = {
		{ { -1.f, -0.0f,-1.f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  1.f, -0.0f,-1.f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { -1.f, -0.0f, 1.f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  1.f, -0.0f, 1.f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }
	};
	mesh.indices =
	{
		0, 1, 2, 2, 1, 3,
		0, 2, 1, 2, 3, 1,
	};
	return mesh;
}

void Square::UpdateHeightMap()
{
	const float dt = std::min(ImGui::GetIO().DeltaTime, 1.f/ static_cast<float>(N));
	const float A = dt * dt / h / h;
	const float B = 2 - 4 * A;

	for (int i = 1; i < N - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			prevHeightMap[i][j] = A * (heightMap[i - 1][j] + heightMap[i + 1][j] +
				heightMap[i][j - 1] + heightMap[i][j + 1]) + B * heightMap[i][j] - prevHeightMap[i][j];
		}
	}

	std::swap(prevHeightMap, heightMap);

	heightMap[100][100] += 0.25f;
}
