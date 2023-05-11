#pragma once
#include "OrbitEngine/Renderer.h"

int main(int argc, char** argv)
{
	OrbitEngine::Renderer renderer = OrbitEngine::Renderer(1024, 600, "Orbit Engine");
	while (!renderer.ShouldWindowClose())
	{
		renderer.Render();
	}
	return 0;
}