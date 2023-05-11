#include "Renderer.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include <cstdio>
#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <stdexcept>

namespace OrbitEngine
{
	const bgfx::ViewId kClearView = 0;

	void glfw_sizeCallback(GLFWwindow* window, int width, int height)
	{
		bgfx::reset(width, height, BGFX_RESET_VSYNC);
		bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	}

	static void glfw_errorCallback(int error, const char* description)
	{
		fprintf(stderr, "GLFW error %d: %s\n", error, description);
	}

	class GLFWException : public std::exception
	{
	public:
		const char* what()
		{
			return "There was an issue with GLFW!";
		}
	};

	class BGFXException : public std::exception
	{
	public:
		const char* what()
		{
			return "There was an issue with BGFX!";
		}
	};

	Renderer::Renderer(int width, int height, const char* title)
	{
		glfwSetErrorCallback(glfw_errorCallback);
		if (!glfwInit())
		{
			throw GLFWException();
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window)
		{
			throw GLFWException();
		}

		bgfx::Init init;
		init.platformData.nwh = glfwGetWin32Window(window);

		init.resolution.width = width;
		init.resolution.height = height;
		init.resolution.reset = BGFX_RESET_VSYNC;

		if (!bgfx::init(init))
		{
			throw BGFXException();
		}

		bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
		bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	}

	Renderer::~Renderer()
	{
		bgfx::shutdown();
		glfwTerminate();
	}

	bool Renderer::ShouldWindowClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Renderer::Render()
	{
		glfwPollEvents();

		bgfx::touch(kClearView);

		bgfx::frame();
	}

}
