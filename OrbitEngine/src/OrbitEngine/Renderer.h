#pragma once
#include "Core.h"

struct GLFWwindow;

namespace OrbitEngine
{
	class ORBIT_API Renderer
	{
	public:
		Renderer(int width, int height, const char* title);
		~Renderer();
		void Render();
		bool ShouldWindowClose() const;

	private:
		GLFWwindow* window;
	};
}
